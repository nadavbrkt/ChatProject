/*
 * P2PClient.h
 *
 *  Created on: Apr 16, 2016
 *      Author: user
 */

#include "TCPSocket.h"
#include "MThread.h"

#ifndef P2PCLIENT_H_
#define P2PCLIENT_H_


using namespace std;

namespace npl {

class P2PClient : public MThread  {
private:
	TCPSocket * client;
	pthread_mutex_t mutex;
public:
	P2PClient(string peerIp, int port);
	virtual ~P2PClient();
	virtual void run();
	virtual int write(string msg) {return client->write(msg);};
	TCPSocket * getSocket();
	void close();
	bool isAlive() {return client->isAlive();};
	int bytesToInt(const char * input);
};
}
#endif /* P2PCLIENT_H_ */
