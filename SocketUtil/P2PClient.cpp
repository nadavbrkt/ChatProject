/*
 * P2PClient.cpp
 *
 *  Created on: Apr 16, 2016
 *      Author: user
 */

#include "P2PClient.h"
#include "TCPSocket.h"
#include "TCPMessengerProtocol.h"
#include "string.h"
#include <unistd.h>
using namespace std;
using namespace npl;

P2PClient::P2PClient(string peerIp, int port) {
	// TODO Auto-generated constructor stub
	client = new TCPSocket(peerIp, port);
	pthread_mutex_init(&mutex,NULL);

	this->start();
}

P2PClient::~P2PClient() {
	// TODO Auto-generated destructor stub
	client->close();
	delete(client);
}

void P2PClient::run() {
	char buffer[50];
	int msgSize = 0;
	int readSize = 4;
	string srv = client->peerAddr();
	memset(buffer,0,50);
	while(((msgSize = client->read(buffer, readSize)) >= 0) && (client->isAlive())) {
		if(msgSize > 0) {
			switch (bytesToInt(buffer)) {
				case SEND_MSG_TO_PEER:
					memset(buffer,0,readSize);
					client->read(buffer, readSize);
					readSize = bytesToInt(buffer);
					memset(buffer,0,readSize);
					client->read(buffer, readSize);
					cout << endl << "Recived : " << buffer << endl << ">> ";
					break;
				case SESSION_REFUSED:
					cout << endl << SESSION_REFUSED_MSG << endl << ">> ";
					memset(buffer,0,readSize);
					break;
				case SESSION_ESTABLISHED:
					cout << endl << "Connection established" << endl << ">> ";
					memset(buffer,0,readSize);
					break;
					break;
				case CLOSE_SESSION_WITH_PEER:
					cout << endl << "Session closed" << endl << ">> ";
					memset(buffer,0,readSize);
					break;
				default:
					break;
			}
			readSize = 4;
			memset(buffer,0,50);
		}

		sleep(1);
	}


	std::cout << endl << "Closed connection to server " << srv << endl;
}

TCPSocket * P2PClient::getSocket() {
	return client;
}

void P2PClient::close() {
	client->close();
}

int npl::P2PClient::bytesToInt(const char * input)
{
	unsigned char * bytes = (unsigned char *) input;
	//cout << "1: " << (unsigned char)input[3]<< " 2: " << (unsigned char)input[2]<< " 3: "<<(unsigned char) input[1]<< " 4: " << input[0]<<endl;
	return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}
