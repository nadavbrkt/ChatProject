/*
 * Dispatcher.cpp
 *
 *  Created on: May 14, 2016
 *      Author: user
 */

#include "Dispatcher.h"
#include <string.h>
#include "Functions.h"
#include "TCPMessengerProtocol.h"
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <algorithm>
#include <stdio.h>
#include <sstream>
#include "Broker.h"

using namespace std;
using namespace npl;

Dispatcher::Dispatcher() : MultipleTCPSocketListener() {
	// TODO Auto-generated constructor stub
	_isAlive = true;
	_brokers = vector<Broker *>();
}

Dispatcher::~Dispatcher() {
	// TODO Auto-generated destructor stub
}

void npl::Dispatcher::run() {
	TCPSocket * readySock = NULL;
	int readSize = 4;
	char buffer[readSize];

	memset(&buffer,0,readSize);

	// Runs until death
	while(_isAlive == true) {
		readySock = getReadySocket();

		// Reads data from socket
		if (readySock != NULL) {
			readySock->read(buffer, readSize);
			action(npl::bytesToInt(buffer), readySock);
			memset(&buffer,0,readSize);
		}
		readySock = NULL;

		sleep(1);
	}
}

void npl::Dispatcher::close() {
	_isAlive = false;

	// Close all brokers
	for (int i = 0; i < (int)_brokers.size(); ++i) {
		_brokers[i]->close();
	}

	// Close all connections
	for (int i = 0; i < (int) tcpSockets.size(); ++i) {
		tcpSockets[i]->write(npl::intToBytes(EXIT));
	}

	this->closeAll();
}

void npl::Dispatcher::action(int command, TCPSocket * sock) {
	int readSize = 4;
	char buffer[50];
	string delimeter = ":";
	string input = "";
	string src = "";
	stringstream port;
	TCPSocket * partner;

	memset(buffer, 0, 50);

	// Gets command
	switch (command) {
		// Open broker
		case OPEN_SESSION_WITH_PEER:
			cout << "Open new session with peer " << sock->peerAddr() << ":"
				 << sock->getPort() << " -> ";

			// Read ip size
			sock->read(buffer, readSize);
			readSize = bytesToInt(buffer);

			// Read ip
			memset(buffer, 0, readSize);
			sock->read(buffer, readSize);

			// Reads data to string
			input = string(buffer);
			cout << input << endl;

			// Search for partber sock
			partner = findSock(input.substr(0,input.find(delimeter)),
					atoi((input.substr(input.find(delimeter) + 1)).c_str()));

			// If exists
			if (partner == NULL) {
				cout << "Error establishing session" << endl;
				sock->write(intToBytes(SESSION_REFUSED));
			} else {
				cout << "Session established" << endl;

				// Opens session
				partner->write(intToBytes(OPEN_SESSION_WITH_PEER));

				// Gets port and set address
				port << sock->getPort();
				src = sock->peerAddr().c_str() + string(":") + port.str();
				partner->write(intToBytes(src.length()));
				partner->write(src);

				sock->write(intToBytes(SESSION_ESTABLISHED));

				// Adds to brokers
				_brokers.push_back(new Broker(sock, partner));
				_brokers[_brokers.size() - 1]->start();
			}

			// Clear data
			partner = NULL;
			input = "";
			memset(buffer, 0, readSize);
			readSize = 4;
			break;
		// Close socket
		case EXIT:
			removeSock(sock);
			sock->close();
			cout << "Close connection from " << sock->peerAddr() << endl;
			break;
		// Close socket
		case 0:
			removeSock(sock);
			sock->close();
			cout << "Close connection from " << sock->peerAddr() << endl;
			break;
		default:
			cout << "Recived " << command << " command from " << sock->peerAddr() << endl;
			break;
	}
}

void npl::Dispatcher::removeSock(TCPSocket * sock) {
	// Clear from FD
	FD_CLR(sock->getFd(), &tcpSocketsFd);

	// Delete from vector
	for (int i = 0; i < (int) tcpSockets.size(); ++i) {
		if (tcpSockets[i]->getFd() == sock->getFd())
			tcpSockets.erase(tcpSockets.begin() + i);
	}
}

TCPSocket * npl::Dispatcher::findSock(string ip, int port) {

	for (int i = 0; i < (int) tcpSockets.size(); ++i) {
 		if ((tcpSockets[i]->peerAddr().compare(ip) == 0) && (tcpSockets[i]->getPort() == port))
			return (tcpSockets[i]);
	}

	return NULL;
}

Dispatcher* npl::Dispatcher::getInstance() {
	if (_dispatcherInstance == NULL) {
		_dispatcherInstance = new Dispatcher();
	}

	return _dispatcherInstance;
}
