/*
 * MultipleTCPSocketListener.cpp
 *
 *  Created on: Apr 16, 2016
 *      Author: user
 */

#include "MultipleTCPSocketListener.h"
#include <stdio.h>
#include <sys/select.h>
using namespace std;
using namespace npl;

MultipleTCPSocketListener::MultipleTCPSocketListener() {
	// TODO Auto-generated constructor stub
	FD_ZERO(&tcpSocketsFd);
	tcpSockets = vector<TCPSocket *>();
	numfd = 0;
	_time.tv_sec = 1;
	_time.tv_usec = 0;
}

MultipleTCPSocketListener::~MultipleTCPSocketListener() {
	// TODO Auto-generated destructor stub
	closeAll();
	tcpSockets.clear();
}

void MultipleTCPSocketListener::addSocket(TCPSocket & sock) {
	FD_SET(sock.getFd(), &tcpSocketsFd);
	tcpSockets.push_back(&sock);

	if (numfd < sock.getFd()) {
		numfd = sock.getFd();
	}
}

void MultipleTCPSocketListener::addMultiSocket(vector<TCPSocket *> sockets) {
	for(int i = 0; i < (int) sockets.size(); i++) {
		FD_SET(sockets[i]->getFd(), &tcpSocketsFd);
		tcpSockets.push_back(sockets[i]);
		if (numfd < sockets[i]->getFd()) {
			numfd = sockets[i]->getFd();
		}
	}
}

TCPSocket * MultipleTCPSocketListener::getReadySocket() {
	fd_set read_fd = tcpSocketsFd;

	if (select(numfd+1 , &read_fd, NULL, NULL, &_time) < 0 ) {
		perror("Select error");
		return NULL;
	}

	for (int i = 0; i < numfd+1; i++) {
		if(FD_ISSET(i, &read_fd)) {
			return &getSocketbyDesc(i);
		}
	}

	return NULL;
}

TCPSocket & MultipleTCPSocketListener::getSocketbyDesc(int fd) {
	for(int i = 0; i < (int) tcpSockets.size(); i++) {
		if(fd == tcpSockets[i]->getFd()) {
			return *tcpSockets[i];
		}
	}
}

void MultipleTCPSocketListener::closeAll() {
	for (int i = 0; i < (int) tcpSockets.size(); ++i) {
		tcpSockets[i]->close();
	}
}

int npl::MultipleTCPSocketListener::getAmountConnection() {
	int size = 0;
	for (int i = 0; i < (int) tcpSockets.size(); ++i) {
		if (tcpSockets[i]->isAlive())
			size++;
	}

	return size;
}

int MultipleTCPSocketListener::replyAll(const string& msg) {
	for (int i = 0; i < (int) tcpSockets.size(); ++i) {
		if(tcpSockets[i]->write(msg) < 0)
			return -1;
	}

	return 0;
}
