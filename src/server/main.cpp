//============================================================================
// Name        : yieldCurveAnalyserServer
// Author      : Jean-Mathieu Vermosen
// Version     :
// Copyright   : all rights reserved
// Description : yield curve analysis tool in C++, Ansi-style
//============================================================================

#include <boost/lexical_cast.hpp>

#include <boost/asio.hpp>

#include <server/tcpServer/tcpServer.hpp>

int main(int argc, char** argv) {

	try {

		boost::asio::io_service io_service;

		// create the tcp server
		tcpServer server(io_service, 7171);
		io_service.run();

	} catch (std::exception & e) {

		std::cerr << e.what() << std::endl;

	}

	return 0;

}
