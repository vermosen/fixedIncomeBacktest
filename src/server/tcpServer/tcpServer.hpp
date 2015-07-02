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

	tcpServer(boost::asio::io_service& io_service, int port) // (1)
		: m_acceptor(io_service, tcp::endpoint(tcp::v4(), port)) {

		awaitConnection();																	// wait for connections

	}

private:
	void awaitConnection() {

		boost::shared_ptr<tcpConnection> connection = tcpConnection::create(m_acceptor.get_io_service());

		m_acceptor.async_accept(
			connection->socket(),
			boost::bind(
				&tcpServer::handle_accept,
				this, connection,
				boost::asio::placeholders::error));

	}

	// new connection attempted, create a session
	void handle_accept(boost::shared_ptr<tcpConnection> connection, const boost::system::error_code& error) {

		if (!error) {

			std::cout << "Connection accepted" << std::endl;								// TODO: log
			boost::shared_ptr<session> ptr = session::create(connection, *this);			// create the session
			awaitConnection();																// await for new connection

		} else {

			std::cerr << "Connection rejected" << std::endl;								// TODO: log

		}
	}

	tcp::acceptor m_acceptor	;

};

#endif /* TCPSERVER_HPP_ */
