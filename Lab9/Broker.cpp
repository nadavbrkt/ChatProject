/*
 * Broker.cpp
 *
 *  Created on: May 20, 2016
 *      Author: user
 */

#include "Dispatcher.h"
#include "Functions.h"
#include <string.h>
#include "TCPMessengerProtocol.h"
#include <unistd.h>

using namespace std ;
using namespace npl;


npl::Broker::Broker( TCPSocket * peer1, TCPSocket * peer2)
	: MultipleTCPSocketListener(), _isAlive(true) {

	// Adds socket to broker
	addSocket(*peer1);
	addSocket(*peer2);

	// Remove from dispatcher
	Dispatcher::getInstance()->removeSock(peer1);
	Dispatcher::getInstance()->removeSock(peer2);
}

npl::Broker::~Broker() {
}

void Broker::run() {
	int readSize = 4;
	char buffer[readSize];
	TCPSocket * sender = NULL;
	memset(&buffer,0,readSize);

	// Runs until death
	while(_isAlive == true) {
		sender = getReadySocket();

		// If ready sockets
		if (sender != NULL) {
			// Reads action
			if (sender->read(buffer, readSize) > 0) {
				action(bytesToInt(buffer), sender);
			}
		}

		sender = NULL;
		sleep(1);
	}
}


void npl::Broker::close() {
	replyAll(intToBytes(CLOSE_SESSION_WITH_PEER));
	_isAlive = false;
	Dispatcher::getInstance()->addMultiSocket(MultipleTCPSocketListener::tcpSockets);
}

void npl::Broker::action(int command, TCPSocket * sender) {
	char buffer[50];
	int readSize = 4;

	// Performs an action
	switch (command) {
		// Close session
		case CLOSE_SESSION_WITH_PEER:
			close();
			break;
		// Send msg
		case SEND_MSG_TO_PEER:
			// Reads msg data
			sender->read(buffer, readSize);
			readSize = bytesToInt(buffer);
			memset(buffer,0,readSize);
			sender->read(buffer, readSize);

			// Find sender and sends to reciver
			if(sender->getFd() == tcpSockets[0]->getFd()) {
				tcpSockets[1]->write(intToBytes(SEND_MSG_TO_PEER));
				tcpSockets[1]->write(string(intToBytes(readSize)));
				tcpSockets[1]->write(string(buffer));
			} else {
				tcpSockets[0]->write(intToBytes(SEND_MSG_TO_PEER));
				tcpSockets[0]->write(string(intToBytes(readSize)));
				tcpSockets[0]->write(string(buffer));
			}

			memset(buffer,0,readSize);
			readSize = 4;
			break;
		default:
			break;
	}
}
