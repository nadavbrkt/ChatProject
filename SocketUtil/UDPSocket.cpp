/*
 * UdpSocket.cpp
 *
 *  Created on: Apr 29, 2016
 *      Author: user
 */

#include "UDPSocket.h"
#include <stdio.h>
#include <arpa/inet.h>
using namespace std;
using namespace npl;

UDPSocket::UDPSocket() : Socket(socket (AF_INET, SOCK_DGRAM, 0)) {
	// Binds port as server (default)
	this->bind(UDPPORT);
	bzero(&_recipent, sizeof(_recipent));
	bzero(&_fromAddr, sizeof(_fromAddr));
}

UDPSocket::UDPSocket(int port) : Socket(socket (AF_INET, SOCK_DGRAM, 0)) {
	// TODO Auto-generated constructor stub

	// Binds port as server
	if (this->bind(port) < 0)
		perror("Error binding port");

	bzero(&_recipent, sizeof(_recipent));
	bzero(&_fromAddr, sizeof(_fromAddr));
}

UDPSocket::~UDPSocket() {
	// TODO Auto-generated destructor stub
}

int UDPSocket::sendTo(const string& msg, string ip, int port) {
	// Creates struct
	struct sockaddr_in to;

	// clear the s_in struct
	bzero((char *) &to, sizeof(to));

	//sets the sin address
	to.sin_port = htons(port);
	to.sin_addr.s_addr = htonl(INADDR_ANY);
	to.sin_family = AF_INET;

	// Sends msg
	return sendto(_fileDiscriptor, msg.data(), msg.length(), 0,
				   (struct sockaddr *) & to,sizeof(to));
}

UDPSocket::UDPSocket(const string& ip, int port) : Socket(socket (AF_INET, SOCK_DGRAM, 0)) {
	this->bind(port);
	bzero(&_recipent, sizeof(_recipent));
	bzero(&_fromAddr, sizeof(_fromAddr));

	// Sets client side
	_recipent.sin_port = htons(port);
	_recipent.sin_addr.s_addr = htonl(INADDR_ANY);
	_recipent.sin_family = AF_INET;
}

int UDPSocket::read(char* buff, int length) {
	unsigned int fsize = sizeof(_fromAddr);
	ssize_t n = recvfrom(_fileDiscriptor, buff, length, 0,(struct sockaddr *)&_fromAddr, &fsize);

	return n;
}

int UDPSocket::write(const string& msg) {
	// Chacks if recipent exists
	if(_recipent.sin_port == 0) {
		perror("No open socket");
		return -1;
	}

	// Sends data
	return sendto(_fileDiscriptor, msg.data(), msg.length(), 0,
				   (struct sockaddr *) & _recipent,sizeof(_recipent));
}

int UDPSocket::reply(const string & msg) {
	if(_fromAddr.sin_port == 0) {
		perror("No open socket");
		return -1;
	}

	return sendto(_fileDiscriptor, msg.data(), msg.length(), 0,
				   (struct sockaddr *) & _fromAddr,sizeof(_fromAddr));
}




