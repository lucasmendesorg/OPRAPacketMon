/*
	The OPRA Multi-Cast Packet Monitor
		(c) 2014 Lucas Mendes <lucas AT lucasmendes.org>
*/

#include <PacketCounter.h>

CPusherThread *CPusherThread::__instance = NULL;
std::string CPusherThread::m_ifnet;
std::string CPusherThread::m_group;
unsigned short CPusherThread::m_port;

int CPusherThread::getQueueCount()
{
	return m_queue.size();
}

std::string CPusherThread::getGroup()
{
	return m_group;
}

unsigned short CPusherThread::getPort()
{
	return m_port;
}

void CPusherThread::configure(const char *ifnet, const char *group, unsigned short port)
{
	m_ifnet = ifnet;
	m_group = group;
	m_port = port;
}

void *CPusherThread::threadHelper(void *ptr)
{
	CPusherThread *self = static_cast<CPusherThread *>(ptr);
	self->run();
	return NULL;
}

void CPusherThread::pushPacket(PACKET packet)
{
	m_mutex.lock();
	m_queue.push(packet);
	
	// FIX
//	fprintf(stderr, "m_queue.size() = %ld\r", m_queue.size());
	m_mutex.unlock();
}

PACKET CPusherThread::popPacket()
{
	PACKET packet;
	m_mutex.lock();
	if(m_queue.empty() == false) {
		packet = m_queue.front();
		m_queue.pop();
	} else {
		packet.size = 0;
	}
	m_mutex.unlock();
	return packet;
}

void CPusherThread::dismiss()
{
	m_runState = THREAD_SHOULD_LEAVE;
}

void CPusherThread::run()
{
	PACKET packet;
	for(; m_runState != THREAD_SHOULD_LEAVE; ) {
		packet.size = recvfrom(m_sd, &packet.body, sizeof(packet.body), 0,
				(struct sockaddr *) &m_address, &m_address_size);
		if(packet.size < 0) {
			perror("CPusherThread: recvfrom");
			dismiss();
			return;
		} if(packet.size == 0) {
			fprintf(stderr, "CPusherThread received zero bytes\n");
			dismiss();
			break;
		}
		pushPacket(packet);
	}
	fprintf(stderr, "CPusherThread is leaving\n");
	sleep(1);
}

CPusherThread::CPusherThread()
{
	struct ip_mreq mreq;
	int k;
	m_runState = THREAD_IS_RUNNING;
	m_sd = socket(AF_INET, SOCK_DGRAM, 0);
	if(m_sd < 0) {
		perror("CPusherThread: socket");
		dismiss();
		return;
	}
	memset(&m_address, 0, sizeof(m_address));
	m_address.sin_family = AF_INET;
	m_address.sin_addr.s_addr = inet_addr(m_group.c_str());	// OPRA_GROUP
	m_address.sin_port = htons(m_port);			// OPRA_PORT
	m_address_size = sizeof(m_address);
	k = RECV_BUFFER_SIZE;
	if(setsockopt(m_sd, SOL_SOCKET, SO_RCVBUF, &k, sizeof(k)) < 0) {
		perror("CPusherThreadL setsockopt SO_RCVBUF");
		close(m_sd);
		dismiss();
		return;
	}
	mreq.imr_multiaddr.s_addr = inet_addr(m_group.c_str());	// OPRA_GROUP      
	mreq.imr_interface.s_addr = inet_addr(m_ifnet.c_str());	// htonl(IF_ADDRESS);
	if (setsockopt(m_sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
		perror("CPusherThread: setsockopt IP_ADD_MEMBERSHIP");
		close(m_sd);
		dismiss();
		return;
	}
	if(bind(m_sd, (struct sockaddr *) &m_address, sizeof(m_address)) < 0) {
		perror("CPusherThread: bind");
		close(m_sd);
		dismiss();
		return;
	}
}

CPusherThread::~CPusherThread()
{
	close(m_sd);
}

CPusherThread *CPusherThread::sharedInstance()
{
	if(CPusherThread::__instance == NULL) {
		CPusherThread::__instance = new CPusherThread();
		pthread_create(&CPusherThread::__instance->m_thread, NULL,
			&CPusherThread::threadHelper, (void *) CPusherThread::__instance);
		
	}
	return CPusherThread::__instance;
}
