/*
 * MultipleTCPSocketListener.h
 *
 *  Created on: Apr 16, 2016
 *      Author: user
 */


#include "TCPSocket.h"
#include <iostream>
#include <vector>
#ifndef MULTIPLETCPSOCKETLISTENER_H_
#define MULTIPLETCPSOCKETLISTENER_H_

using namespace std;

namespace npl {
class MultipleTCPSocketListener {
protected:
	fd_set tcpSocketsFd;
	int numfd;
	struct timeval _time;
	vector<TCPSocket *> tcpSockets;
	TCPSocket & getSocketbyDesc(int fd);
public:
	MultipleTCPSocketListener();
	virtual ~MultipleTCPSocketListener();
	void addSocket(TCPSocket & sock);
	void addMultiSocket(vector<TCPSocket *> sockets);
	TCPSocket * getReadySocket();
	void closeAll();
	int getAmountConnection();
	int replyAll(const string& msg);
};
}
#endif /* MULTIPLETCPSOCKETLISTENER_H_ */
