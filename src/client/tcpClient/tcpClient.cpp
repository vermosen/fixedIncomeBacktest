/*
 * tcpClient.cpp
 *
 *  Created on: May 26, 2015
 *      Author: vermosen
 */


#include <client/tcpClient/tcpClient.hpp>

tcpClient::tcpClient(
	boost::asio::io_service& ios,
	scrolledLogWindow& scroll)

	: m_closing		(false),
	  m_connected	(false),
	  m_ios			(ios),
	  m_timer		(m_ios, boost::posix_time::seconds(1)),
	  m_scroll		(scroll) {}

void tcpClient::connect(boost::asio::ip::tcp::endpoint& endpoint) {

	m_connection = tcpConnection::create(m_ios);
	m_connection->socket().async_connect(endpoint,
		boost::bind(&tcpClient::handle_connect,
		shared_from_this(),
		boost::asio::placeholders::error));

}

void tcpClient::deliver(const message& msg) {

	m_connection->async_write(msg,
		boost::bind(&tcpClient::handle_write_message,
		shared_from_this(),
		boost::asio::placeholders::error));

};

void tcpClient::deliver(const sqlLogin& conn) {

	m_connection->async_write(conn,
		boost::bind(&tcpClient::handle_write_sql_login,
		shared_from_this(),
		boost::asio::placeholders::error));

};

void tcpClient::read_message() {							// wait for incoming message

	if(!m_connected || m_closing) return;

	m_connection->async_read(m_message,						// wait for a new message
		boost::bind(
			&tcpClient::handle_read_message,
			shared_from_this(),
			boost::asio::placeholders::error));

};

void tcpClient::handle_connect(const boost::system::error_code& error) {

	if (m_closing) return;

	if(!error) {

		m_connected = true;
		m_scroll.append("connection to the server was successfull");
		read_message();

	}

};
void tcpClient::handle_read_message(const boost::system::error_code& error) {

	if (!error && !m_closing) {

		m_scroll.append("server replied: " + m_message.m_body);

	}
};

void tcpClient::handle_write_message(const boost::system::error_code& error) {

	if (!error && !m_closing) {

		m_connection->async_write(m_message,
			boost::bind(&tcpClient::handle_write_message,
				shared_from_this(),
				boost::asio::placeholders::error));

	}
};

void tcpClient::handle_write_sql_login(const boost::system::error_code& error) {

	if (!error && !m_closing) {

		m_connection->async_write(m_sqlLogin,
			boost::bind(&tcpClient::handle_write_sql_login,
				shared_from_this(),
				boost::asio::placeholders::error));

	}
};
