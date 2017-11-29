/*
 * File.cpp
 *
 *  Created on: Apr 28, 2016
 *      Author: user
 */

#include "File.h"
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <fcntl.h>

using namespace std;
using namespace npl;


File::File(string path) : FileInterface(this->open(path)) {
	// TODO Auto-generated constructor stub
	if (_fileDiscriptor < 0) {
		perror("Error opening file");
	}

	_aliveStatus = true;
}

File::~File() {
	// TODO Auto-generated destructor stub
	this->close();
}

int File::open(string path) {
	return ::open(path.c_str(), O_RDWR | O_CREAT);
}
