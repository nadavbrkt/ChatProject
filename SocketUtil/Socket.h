/*
 * Socket.h
 *
 *  Created on: Apr 28, 2016
 *      Author: user
 */

#include "FileInterface.h"
#include <inttypes.h>
#include <netinet/in.h>

#ifndef SOCKET_H_
#define SOCKET_H_

using namespace std;
namespace npl {

class Socket : public FileInterface {
protected:
	struct sockaddr_in _netAddr;
	struct sockaddr_in _fromAddr;
public:
	Socket(int fd);
	Socket();
	virtual ~Socket();

	// Bind socket
	virtual int bind(int port);

	// Get from address
	virtual string fromAddr();
};
}
#endif /* SOCKET_H_ */
