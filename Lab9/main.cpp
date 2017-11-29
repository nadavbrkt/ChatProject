
#include <iostream>
#include "Server.h"
#include "Dispatcher.h"
using namespace std;
using namespace npl;

npl::Dispatcher * npl::Dispatcher::_dispatcherInstance = NULL;

int main(int argc, char **argv) {
	Server * srv;
	srv = new Server();
	srv->start();

	srv->waitForThread();

}


