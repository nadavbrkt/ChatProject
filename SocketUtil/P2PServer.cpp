/*
 * P2PServer.cpp
 *
 *  Created on: Apr 16, 2016
 *      Author: user
 */

#include "P2PServer.h"
#include "TCPSocket.h"
#include "string.h"
#include <vector>
#include <unistd.h>


using namespace std;
using namespace npl;

P2PServer::P2PServer(int port) : _connections(MultipleTCPSocketListener()) {
	// TODO Auto-generated constructor stub
	server = new TCPSocket(port);
	pthread_mutex_init(&mutex,NULL);

	this->start();
}

P2PServer::~P2PServer() {
	// TODO Auto-generated destructor stub
	this->closeListener();
	this->closeConnections();
	delete(server);
}

void P2PServer::run() {
	char buffer[50];
	TCPSocket * tempConn = NULL;


	// Wait for connection
	while (server->isAlive())  {
		server->listen();
		tempConn = server->accept();

		if(tempConn != NULL) {
			_connections.addSocket(*tempConn);
			cout << "Start Connection from : " << tempConn->fromAddr() << endl;
		}

		tempConn = NULL;
		while((tempConn = _connections.getReadySocket()) != NULL) {
			tempConn->read(buffer,50);
			cout << "Recived from : " << tempConn->fromAddr() << " -> " << buffer << endl;
		}


		tempConn = NULL;

		sleep(1);
	}

	cout << "Closed Listener Server" << endl;
}

void P2PServer::closeConnections() {
	_connections.closeAll();
}

void P2PServer::closeListener() {
	server->close();
}
