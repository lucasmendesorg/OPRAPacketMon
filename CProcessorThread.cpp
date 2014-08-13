/*
	The OPRA Multi-Cast Packet Monitor
		(c) 2014 Lucas Mendes <lucas AT lucasmendes.org>
*/

#include <PacketCounter.h>

CProcessorThread *CProcessorThread::__instance = NULL;

void CProcessorThread::waitFor()
{
	pthread_join(m_thread, NULL);
}

unsigned int CProcessorThread::getDup()
{
	return m_dup;
}

unsigned int CProcessorThread::getLoss()
{
	return m_loss;
}

void *CProcessorThread::threadHelper(void *ptr)
{
	CProcessorThread *self = static_cast<CProcessorThread *>(ptr);
	self->run();
	return NULL;
}

void CProcessorThread::dismiss()
{
	m_runState = THREAD_SHOULD_LEAVE;
}

static void ProcessOpraHeader(OPRA_HEADER *header)
{
	header->blockSize = ((header->blockSize & 0xFF00) >> 8) | ((header->blockSize & 0x00FF) << 8);
	header->blockSequenceNumber = ((header->blockSequenceNumber & 0xFF000000) >> 24) | ((header->blockSequenceNumber & 0x00FF0000) >> 8)
					| ((header->blockSequenceNumber & 0x0000FF00) << 8) | ((header->blockSequenceNumber & 0x000000FF) << 24);
	header->blockChecksum = ((header->blockChecksum & 0xFF00) >> 8) | ((header->blockChecksum & 0x00FF) << 8);
}

void CProcessorThread::run()
{
	PACKET packet;
	OPRA_HEADER *header;
	for(u_int32_t lastBlockSequenceNumber = 0; m_runState != THREAD_SHOULD_LEAVE; ) {
		for(packet.size = 0; packet.size == 0; packet = m_pusher->popPacket()) {
			usleep(1);
		}
		header = reinterpret_cast<OPRA_HEADER *>(&packet.body);
		ProcessOpraHeader(header);
		if(header->dataFeedIndicator == 'O') {
/*			fprintf(stderr, "OPRA Version %u, BlockSize %5d, RetransmissionIndicator %u, BlockSequenceNumber %u\n",
				header->version, header->blockSize, header->retransmissionIndicator, header->blockSequenceNumber);
*/			if(lastBlockSequenceNumber != 0) {
				if((header->blockSequenceNumber - 1) != lastBlockSequenceNumber) {
					if(header->blockSequenceNumber == lastBlockSequenceNumber) {
						fprintf(stderr, "DUP packet w/ BlockSequenceNumber %u\n", header->blockSequenceNumber);
						++m_dup;
					} else {
						fprintf(stderr, "Lost packet w/ BlockSequenceNumber %u\n", header->blockSequenceNumber - 1);
						fprintf(stderr, "\tprevious BlockSequencerNumber %u\n", lastBlockSequenceNumber);
						fprintf(stderr, "\tcurrent  BlockSequenceNumber %u\n", header->blockSequenceNumber);
						++m_loss;
					}
				}
			}
			lastBlockSequenceNumber = header->blockSequenceNumber;
		}
	}
	fprintf(stderr, "CProcessorThread is leaving\n");
	sleep(1);
}

CProcessorThread::CProcessorThread()
{
	m_runState = THREAD_IS_RUNNING;
	m_loss = 0;
	m_dup = 0;
	m_pusher = CPusherThread::sharedInstance();
}

CProcessorThread::~CProcessorThread()
{
}

CProcessorThread *CProcessorThread::sharedInstance()
{
	if(CProcessorThread::__instance == NULL) {
		CProcessorThread::__instance = new CProcessorThread();
		pthread_create(&CProcessorThread::__instance->m_thread, NULL,
			&CProcessorThread::threadHelper, (void *) CProcessorThread::__instance);
		
	}
	return CProcessorThread::__instance;
}
