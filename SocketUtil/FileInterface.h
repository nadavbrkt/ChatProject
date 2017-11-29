/*
 * FileInterface.h
 *
 *  Created on: Apr 28, 2016
 *      Author: user
 */
#include <strings.h>
#include <iostream>

#ifndef FILEINTERFACE_H_
#define FILEINTERFACE_H_

using namespace std;

namespace npl {

class FileInterface {
protected:
	int _fileDiscriptor;
	bool _aliveStatus;
	FileInterface(int fd);
	FileInterface();
public:
	virtual ~FileInterface();

	// Read data from descriptor
	virtual int read(char * buff, int length);

	// Write data from descriptor
	virtual int write(const string & msg);

	// Close descriptor
	virtual int close();

	// Return descriptor
	virtual int getFd() {return _fileDiscriptor;};

	// Return is alive
	virtual bool isAlive() {return _aliveStatus;};
};
}
#endif /* FILEINTERFACE_H_ */
