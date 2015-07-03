/*
 * tcpServer.hpp
 *
 *  Created on: May 21, 2015
 *      Author: vermosen
 */

#ifndef TCPSERVER_HPP_
#define TCPSERVER_HPP_

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <server/session/session.hpp>
#include <shared/tcpConnection/tcpConnection.hpp>

class session;

class tcpServer {

public:

	tcpServer(boost::asio::io_service&, int);

private:
	void awaitConnection();

	void handle_connection(																		// if succeeded, creates a session
		boost::shared_ptr<tcpConnection>,
		const boost::system::error_code&);

	tcp::acceptor m_acceptor;

};

#endif /* TCPSERVER_HPP_ */
