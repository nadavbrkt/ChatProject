/*
 * Broker.h

 *
 *  Created on: May 20, 2016
 *      Author: user
 */


#ifndef BROKER_H_
#define BROKER_H_

#include "MultipleTCPSocketListener.h"
#include "MThread.h"

using namespace std;

namespace npl {

class Broker : public MThread, public MultipleTCPSocketListener {
private:
	bool _isAlive;
public:
	Broker( TCPSocket * peer1, TCPSocket * peer2);
	virtual ~Broker();

	virtual void run();
	virtual void close();
	void action(int command, TCPSocket * sender);
};
}

#endif /* BROKER_H_ */
