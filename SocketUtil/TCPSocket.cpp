/*
 * TCPSocket.cpp
 *
 *  Created on: Apr 29, 2016
 *      Author: user
 */

#include "TCPSocket.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace npl;

TCPSocket::TCPSocket(int connected_sock,struct sockaddr_in serverAddr,struct sockaddr_in peerAddr)
	: Socket(connected_sock) {
	bzero(&(this->_serverAddr), sizeof(this->_serverAddr));
	bzero(&(this->_peerAddr), sizeof(this->_peerAddr));
	bzero(&(this->_fromAddr), sizeof(this->_fromAddr));

	memcpy(&(this->_serverAddr), &serverAddr, sizeof(_serverAddr));
	memcpy(&(this->_peerAddr), &peerAddr, sizeof(_peerAddr));
	memcpy(&(this->_fromAddr), &peerAddr, sizeof(_fromAddr));

	_aliveStatus = true;
}

TCPSocket::TCPSocket(int port) : Socket(socket(AF_INET, SOCK_STREAM, 0)) {
	// TODO Auto-generated constructor stub
	// Initialize data
	bzero(&_serverAddr, sizeof(_serverAddr));

	_serverAddr.sin_family = AF_INET;
	_serverAddr.sin_port = htons(port);

	if (this->bind(port) < 0) {
		perror("Error binding port");
		this->close();
	}

	_aliveStatus = true;
}

TCPSocket::TCPSocket(const string& peerIp, int port) : Socket(socket(AF_INET, SOCK_STREAM, 0)){
	// TODO Auto-generated constructor stub
	bzero(&_peerAddr, sizeof(_peerAddr));

	_peerAddr.sin_family = AF_INET;
	_peerAddr.sin_addr.s_addr = inet_addr(peerIp.c_str());
	_peerAddr.sin_port = htons(port);

	// Connect to server
	if (this->connect(peerIp, port)) {
		perror("Error establishing connection to server");
		this->close();
	}

	_aliveStatus = true;
}

TCPSocket::~TCPSocket() {
	// TODO Auto-generated destructor stub
}

int TCPSocket::listen() {
	return ::listen(_fileDiscriptor, 1);
}

TCPSocket* TCPSocket::accept() {
	struct sockaddr_in their_addr;
	socklen_t len = sizeof(their_addr);
	int new_fd = 0;

	// Create a new socket
	if ((new_fd = ::accept(_fileDiscriptor, (struct sockaddr *) & their_addr, &len)) < 0)
		return NULL;

	return new TCPSocket(new_fd, _serverAddr, their_addr);
}

int TCPSocket::connect(const string& peerIp, int port) {
	return ::connect(_fileDiscriptor, (struct sockaddr *) & _peerAddr, sizeof(_peerAddr));
}

int npl::TCPSocket::close() {
	shutdown(_fileDiscriptor, SHUT_RD);
	return FileInterface::close();
}
