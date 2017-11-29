#include "TCPSocket.h"
#include <vector>
#include <sstream>

namespace npl {

static string intToBytes(int paramInt)
{
	stringstream outString;
    vector<unsigned char> arrayOfByte(4);
    for (int i = 0; i < 4; i++)
        arrayOfByte[3 - i] = (paramInt >> (i * 8));

 	for (int i = 0; i < (int) arrayOfByte.size(); ++i) {
 		outString << arrayOfByte[i];
 	}

 	return outString.str();
};

static int bytesToInt(const char * input)
{
	unsigned char * bytes = (unsigned char *) input;
	//cout << "1: " << (unsigned char)input[3]<< " 2: " << (unsigned char)input[2]<< " 3: "<<(unsigned char) input[1]<< " 4: " << input[0]<<endl;
	return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
};
}
