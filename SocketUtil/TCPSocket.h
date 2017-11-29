/*
 * TCPSocket.h
 *
 *  Created on: Apr 29, 2016
 *      Author: user
 */

#include "Socket.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_

using namespace std;

namespace npl {
class TCPSocket : public Socket {
private:
	struct sockaddr_in _serverAddr;
	struct sockaddr_in _peerAddr;
	TCPSocket(int connected_sock,struct sockaddr_in serverAddr,struct sockaddr_in peerAddr);
public:
	TCPSocket(int port);
	virtual ~TCPSocket();

	// Constructor creates TCP client socket
	TCPSocket(const string& peerIp, int port);

	// Perform listen on server socket
	int listen();

	// Connect to remote host
	int connect(const string& peerIp, int port);

	// Perform accept on server socket
	TCPSocket * accept();

	virtual int close();

	string peerAddr() {
		return inet_ntoa(_peerAddr.sin_addr);
	}

	int getPort() {
		return (int) ntohs(_peerAddr.sin_port);
	}
};
}
#endif /* TCPSOCKET_H_ */
