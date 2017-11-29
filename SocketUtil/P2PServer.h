/*
 * P2PServer.h
 *
 *  Created on: Apr 16, 2016
 *      Author: user
 */

#include <pthread.h>
#include <string>
#include "MThread.h"
#include "MultipleTCPSocketListener.h"


#ifndef P2PSERVER_H_
#define P2PSERVER_H_

#define PORT 10152

using namespace std;
namespace npl {

class P2PServer : public MThread {
private:
	TCPSocket * server;
	pthread_mutex_t mutex;
	MultipleTCPSocketListener _connections;
public:
	P2PServer(int port);
	virtual ~P2PServer();
	virtual void run();
	void closeConnections();
	void closeListener();
	bool isAliveServer() {return (_connections.getAmountConnection() > 0);};
	int replyAll(const string& msg) {return _connections.replyAll(msg);};
};
}
#endif /* P2PSERVER_H_ */
