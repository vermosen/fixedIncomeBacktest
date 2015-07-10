/*
 * tcpClient.cpp
 *
 *  Created on: May 26, 2015
 *      Author: vermosen
 */


#include <client/tcpClient/tcpClient.hpp>

boost::shared_ptr<tcpClient> tcpClient::create(						// factory
		boost::asio::io_service& ios, scrolledLogWindow& win) {

	boost::shared_ptr<tcpClient> m_client(new tcpClient(ios, win));

	return m_client;

};

tcpClient::tcpClient(
	boost::asio::io_service& ios,
	scrolledLogWindow& scroll)

	: m_closing		(false),
	  m_connected	(false),
	  m_ios			(ios),
	  m_timer		(m_ios, boost::posix_time::seconds(1)),
	  m_scroll		(scroll) {}

void tcpClient::connect(boost::asio::ip::tcp::endpoint& endpoint) {

	m_connection = boost::shared_ptr<tcpConnection>(new tcpConnection(m_ios));

	m_thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&tcpClient::threadAction, this)));

	m_connection->socket().async_connect(endpoint,
		boost::bind(&tcpClient::handle_connect,
		this, boost::asio::placeholders::error));

}

void tcpClient::deliver(const message& msg) {

	m_connection->async_write(msg,
		boost::bind(&tcpClient::handle_write_message,
		shared_from_this(),
		boost::asio::placeholders::error));

};

//void tcpClient::deliver(const sqlLogin& login) {
//
//	m_connection->async_write(login,
//		boost::bind(&tcpClient::handle_write_sql_login,
//		shared_from_this(),
//		boost::asio::placeholders::error));
//
//};

void tcpClient::read_message() {							// wait for incoming message

	if(m_closing) return;

	m_connection->async_read(m_message,						// wait for a new message
		boost::bind(
			&tcpClient::handle_read_message,
			shared_from_this(),
			boost::asio::placeholders::error));

};

void tcpClient::handle_connect(const boost::system::error_code & error) {

	if (m_closing) return;

	if(!error) {

		m_connected = true;
		m_scroll.append("connection to the server was successfull");
		//read_message();

	} else {

		std::cout << error << std::endl;

	}

};
void tcpClient::handle_read_message(const boost::system::error_code & error) {

	if (!error && !m_closing) {

		m_scroll.append("server replied: " + m_message.m_body);

	}
};

void tcpClient::handle_write_message(const boost::system::error_code & error) {

	if (!error && !m_closing) {

		//m_connection->async_write(m_message,
		//	boost::bind(&tcpClient::handle_write_message,
		//		shared_from_this(),
		//		boost::asio::placeholders::error));

	}
};

//void tcpClient::handle_write_sql_login(const boost::system::error_code& error) {
//
//	if (!error && !m_closing) {
//
//		m_connection->async_write(m_sqlLogin,
//			boost::bind(&tcpClient::handle_write_sql_login,
//				shared_from_this(),
//				boost::asio::placeholders::error));
//
//	}
//};
