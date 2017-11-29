/*
 * Tcpp2pMessenger.h
 *
 *  Created on: Apr 16, 2016
 *      Author: user
 */

#ifndef TCPP2PMESSENGER_H_
#define TCPP2PMESSENGER_H_

#include "P2PServer.h"
#include "P2PClient.h"

using namespace std;

namespace npl {

class Tcpp2pMessenger {
private:
	P2PClient * cli;
	P2PServer * srv;
public:
	Tcpp2pMessenger(int port);
	virtual ~Tcpp2pMessenger();
	TCPSocket * getClientSock() { return cli->getSocket();};
	bool open(string peerIp, int port);

	int send(string msg);

	int reply(const string& msg);

	void close();

	bool isActiveClientSession() {return cli->isAlive();};

	bool isActiveServerSession() {return srv->isAliveServer();};


};
}
#endif /* TCPP2PMESSENGER_H_ */
