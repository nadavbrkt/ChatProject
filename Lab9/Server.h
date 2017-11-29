/*
 * Server.h
 *
 *  Created on: May 14, 2016
 *      Author: user
 */

#ifndef SERVER_H_
#define SERVER_H_
#include "TCPSocket.h"
#include "MThread.h"
using namespace std;

namespace npl {
class Server : public MThread {
private:
	TCPSocket _server;
public:
	Server();
	virtual ~Server();

	virtual void run();

	// Close all connections
	void closeConnections();

	// Close listener
	void closeListener() {_server.close();};

	// Waits for thread
	virtual void waitForThread();
};
}

#endif /* SERVER_H_ */
