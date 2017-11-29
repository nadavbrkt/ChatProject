/*
 * Tcpp2pMessenger.cpp
 *
 *  Created on: Apr 16, 2016
 *      Author: user
 */

#include "Tcpp2pMessenger.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
using namespace npl;

Tcpp2pMessenger::Tcpp2pMessenger(int port) {
	// TODO Auto-generated constructor stub
	srv = new P2PServer(port);
	cli = NULL;
}

Tcpp2pMessenger::~Tcpp2pMessenger() {
	// TODO Auto-generated destructor stub
	this->close();
	delete(srv);
	delete(cli);
}

bool Tcpp2pMessenger::open(string peerIp, int port) {
	cli = new P2PClient(peerIp, port);
	return cli->isAlive();
}

int Tcpp2pMessenger::send(string msg) {
	string newMsg = "";
	stringstream size;
	size << msg.length();
	newMsg = string("[") + size.str() +  string("][") + msg + string("]");
	return cli->getSocket()->write(newMsg);
}

int Tcpp2pMessenger::reply(const string& msg) {
	string newMsg = "";
	stringstream size;
	size << msg.length();
	newMsg = string("[") + size.str() +  string("][") + msg + string("]");

	vector<TCPSocket *> socks = vector<TCPSocket *>();
	return srv->replyAll(newMsg);
}

void Tcpp2pMessenger::close() {
	if( isActiveServerSession()) {
		srv->closeConnections();
	}

	if (cli != NULL) {
		if (isActiveClientSession()) {

			cli->close();
			cli->waitForThread();
		}
	}
	srv->closeListener();
	srv->waitForThread();
}
