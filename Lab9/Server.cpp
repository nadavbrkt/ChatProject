/*
 * Server.cpp
 *
 *  Created on: May 14, 2016
 *      Author: user
 */

#include "Server.h"
#include "TCPMessengerProtocol.h"
#include <unistd.h>
#include "Dispatcher.h"
using namespace std;
using namespace npl;

Server::Server() : _server(MSNGR_PORT) {
	// TODO Auto-generated constructor stub
}

Server::~Server() {
	// TODO Auto-generated destructor stub
	npl::Dispatcher::getInstance()->close();
	_server.close();
}

void npl::Server::run() {
	TCPSocket * tempConn = NULL;

	// Starts dispatcher
	npl::Dispatcher::getInstance()->start();

	// Wait for connection
	while (_server.isAlive())  {
		_server.listen();

		// Accepts connection
		tempConn = _server.accept();

		// Adds it to dispatcher
		if(tempConn != NULL) {
			npl::Dispatcher::getInstance()->addSocket(*tempConn);
			cout << "Start Connection from : " << tempConn->fromAddr()
				 << ":" << tempConn->getPort() << endl;
		}

		tempConn = NULL;

		sleep(1);
	}

	cout << "Closed Listener Server" << endl;
}

void npl::Server::closeConnections() {
	npl::Dispatcher::getInstance()->close();
}

void npl::Server::waitForThread() {
	npl::Dispatcher::getInstance()->waitForThread();
	MThread::waitForThread();
}
