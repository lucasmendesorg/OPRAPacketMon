/*
	The OPRA Multi-Cast Packet Monitor
		(c) 2014 Lucas Mendes <lucas AT lucasmendes.org>
*/

#ifndef PACKETCOUNTER_H
#define PACKETCOUNTER_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <csignal>
#include <queue>
#include <mutex>
#include <unistd.h>
#include <syslog.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PACKET_LIMIT		1024
#define RECV_BUFFER_SIZE	25165824
#define TABLE_SIZE		4294967296

#define THREAD_IS_RUNNING	0
#define THREAD_SHOULD_LEAVE	1

#define MUTEX_UNLOCKED		0
#define MUTEX_LOCKED		1

struct OPRA_HEADER {
	u_int8_t version;
	u_int16_t blockSize;
	u_int8_t dataFeedIndicator;
	u_int8_t retransmissionIndicator;
	u_int8_t sessionIndicator;
	u_int32_t blockSequenceNumber;
	u_int8_t messagesInBlock;
	u_int64_t blockTimestamp;
	u_int16_t blockChecksum;
} __attribute__((packed));

struct PACKET {
	int size;
	char body[PACKET_LIMIT];
};

class CPusherThread
{
	static CPusherThread *__instance;
	static void *threadHelper(void *ptr);
	static std::string m_ifnet;
	static std::string m_group;
	static unsigned short m_port;
	std::queue<PACKET> m_queue;
	std::mutex m_mutex;
	pthread_t m_thread;
	int m_runState;
	int m_sd;
	struct sockaddr_in m_address;
	socklen_t m_address_size;
public:
	int getQueueCount();
	void pushPacket(PACKET p);
	PACKET popPacket();
	void run();
	void dismiss();
	CPusherThread();
	~CPusherThread();
	static std::string getGroup();
	static unsigned short getPort();
	static void configure(const char *ifnet, const char *group, unsigned short port);
	static CPusherThread *sharedInstance();
};

class CProcessorThread
{
	static CProcessorThread *__instance;
	static void *threadHelper(void *ptr);
	CPusherThread *m_pusher;
	pthread_t m_thread;
	int m_runState;
	unsigned int m_loss;
	unsigned int m_dup;
public:
	void waitFor();
	unsigned int getDup();
	unsigned int getLoss();
	void run();
	void dismiss();
	CProcessorThread();
	~CProcessorThread();
	static CProcessorThread *sharedInstance();
};

#endif
