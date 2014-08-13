/*
	The OPRA Multi-Cast Packet Monitor
		(c) 2014 Lucas Mendes <lucas AT lucasmendes.org>
*/

#include <PacketCounter.h>

void SigUsr(int code)
{
	char buffer[1024];
	memset(&buffer, 0, sizeof(buffer));
	CProcessorThread *process = CProcessorThread::sharedInstance();
	snprintf(buffer, sizeof(buffer), "%s/%d -- %u DUP packets, %u lost packets\n",
		CPusherThread::getGroup().c_str(), CPusherThread::getPort(),
		process->getDup(), process->getLoss());
	syslog(3, buffer, strlen(buffer));
}

int main(int argc, char **argp, char **envp)
{
	fprintf(stderr, "The OPRA Multi-Cast Packet Monitor\n");
	fprintf(stderr, "\t(c) 2014 Lucas Mendes <lucas@lucasmendes.org>\n\n");
	
	if(argc < 4) {
		// FIX: Buffer overflow here
		fprintf(stderr, "Try: %s [ifnet-IP] [mcast-group-IP] [mcast-port]\n", argp[0]);
		return 1;
	}
	
	CPusherThread::configure(argp[1], argp[2], atoi(argp[3]));
	
	CPusherThread *pusher = CPusherThread::sharedInstance();
	CProcessorThread *processor = CProcessorThread::sharedInstance();
	
	signal(SIGUSR1, &SigUsr);
	
	fprintf(stderr, "Running..\n\n");
	
	processor->waitFor();
/*	for(;; sleep(1)) {
		fprintf(stderr, "queue entries = %d\r", pusher->getQueueCount());
	}
*/	
	pusher->dismiss();
	processor->dismiss();
	
	delete pusher;
	delete processor;
	return 0;
}
