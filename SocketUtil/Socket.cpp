/*
 * Socket.cpp
 *
 *  Created on: Apr 28, 2016
 *      Author: user
 */

#include "Socket.h"

#include <arpa/inet.h>
#include <strings.h>
#include <sys/socket.h>
#include <string>

using namespace std;
using namespace npl;

Socket::Socket(int fd) : FileInterface(fd) {
	// TODO Auto-generated constructor stub
	// Initialize data
	bzero(&_netAddr, sizeof(_netAddr));
}
Socket::Socket() {
	// TODO Auto-generated constructor stub
	// Initialize data
	bzero(&_netAddr, sizeof(_netAddr));
}
Socket::~Socket() {
	// TODO Auto-generated destructor stub
}

int Socket::bind(int port) {
	bzero(&_netAddr, sizeof(_netAddr));

	// Sets the sin address
	_netAddr.sin_port = htons(port);
	_netAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	_netAddr.sin_family = AF_INET;

	_aliveStatus = true;
	return ::bind(_fileDiscriptor, (struct sockaddr *)&_netAddr, sizeof(_netAddr));
}

string Socket::fromAddr() {
	return inet_ntoa(_fromAddr.sin_addr);
}
