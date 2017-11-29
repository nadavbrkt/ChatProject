/*
 * Dispatcher.h
 *
 *  Created on: May 14, 2016
 *      Author: user
 */

#ifndef DISPATCHER_H_

#define DISPATCHER_H_
#include "Broker.h"
#include "MThread.h"
#include "MultipleTCPSocketListener.h"
using namespace std;

namespace npl{
class Dispatcher : public MThread, public MultipleTCPSocketListener {
private:
	// Singelton
	static Dispatcher * _dispatcherInstance;
	Dispatcher();

	bool _isAlive;
	vector<Broker *> _brokers;
public:
	static Dispatcher * getInstance();

	virtual ~Dispatcher();

	virtual void run();
	virtual void close();

	// Performs an action
	void action(int command, TCPSocket * sock);

	// Remove socket
	void removeSock(TCPSocket * sock);

	virtual TCPSocket * findSock(string ip, int port);
};
}
#endif /* DISPATCHER_H_ */
