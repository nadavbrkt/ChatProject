/*
 * File.h
 *
 *  Created on: Apr 28, 2016
 *      Author: user
 */

#ifndef FILE_H_
#define FILE_H_

#include "FileInterface.h"

using namespace std;

namespace npl {

class File: public FileInterface {
public:
	// Open descriptor path
	File(string path);

	virtual ~File();

	// Open path
	int open(string path);
};
}

#endif /* FILE_H_ */
