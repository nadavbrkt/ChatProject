/*
 * UdpSocket.h
 *
 *  Created on: Apr 29, 2016
 *      Author: user
 */

#include "Socket.h"

#ifndef UDPSOCKET_H_
#define UDPSOCKET_H_

static const int UDPPORT = 10520;

using namespace std;

namespace npl {
class UDPSocket : public Socket {
private:
	struct sockaddr_in _recipent;

public:
	UDPSocket();

	// Starts server
	UDPSocket(int port);

	// Connect to remote server
	UDPSocket(const string& ip, int port);

	virtual ~UDPSocket();

	// Update read method
	virtual int read(char * buff, int length);

	// Update write method
	virtual int write(const string & msg);

	// Sends to remote host
	int sendTo(const string & msg, string ip, int port);

	// Reply to from host
	int reply(const string & msg);
};
}
#endif /* UDPSOCKET_H_ */
