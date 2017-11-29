/*
 * FileInterface.cpp
 *
 *  Created on: Apr 28, 2016
 *      Author: user
 */

#include "FileInterface.h"
#include <unistd.h>
#include <stdio.h>
using namespace std;
using namespace npl;

FileInterface::FileInterface(int fd) {
	// TODO Auto-generated constructor stub
	if (fd < 0){
		perror("Non valid descriptor");
	}

	_fileDiscriptor = fd;
	_aliveStatus = false;
}
FileInterface::FileInterface() {
	// TODO Auto-generated constructor stub
	_aliveStatus = false;
	_fileDiscriptor = 0;
}

FileInterface::~FileInterface() {
	// TODO Auto-generated destructor stub
	close();
}

int FileInterface::read(char * buff, int length) {
	return ::read(_fileDiscriptor, buff, length);
}

int FileInterface::write(const string & msg) {
	return ::write(_fileDiscriptor, msg.c_str(), msg.length());
}


int FileInterface::close() {
	if (_aliveStatus == false)
		return 0;

	_aliveStatus = false;

	::close(_fileDiscriptor);
	_fileDiscriptor = 0;
	return _fileDiscriptor;
}

