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
	  m_work		(ios),
	  m_deadline	(ios),
	  m_scroll		(scroll) {

	m_threads.create_thread(boost::bind(&boost::asio::io_service::run, boost::ref(m_ios)));

}

void tcpClient::connect(boost::asio::ip::tcp::endpoint& endpoint) {

	if (!m_connected) {

		// create the connection object
		m_connection = boost::shared_ptr<tcpConnection>(new tcpConnection(m_ios));

		// start the timer
		m_deadline.expires_from_now(boost::posix_time::seconds(5));

		m_connection->socket().async_connect(endpoint,
			boost::bind(&tcpClient::handle_connect,
			this, boost::asio::placeholders::error));

		m_deadline.async_wait(boost::bind(&tcpClient::check_deadline, this));

	} else {

		throw std::logic_error("client already connected");

	}
}

void tcpClient::disconnect() {

	if (m_connected) {

		m_closing = true;
		m_connection->socket().close();
		m_connection.reset();
		m_connected = false;
		m_closing   = false;

	} else {

		throw std::logic_error("no connection set");

	}
}

void tcpClient::deliver(const message& msg) {

	if (m_connected) {

		m_connection->async_write(msg,
			boost::bind(&tcpClient::handle_write_message,
			shared_from_this(),
			boost::asio::placeholders::error));

	} else {

		throw std::logic_error("no connection set");

	}

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

	if(!error && !m_closing) {

		m_connected = true;
		m_scroll.append("connection to the server was successful");
		read_message();										// wait for new message

	} else {

		m_scroll.append("failed to connect to the server: ");
		m_scroll.append(error.message());

	}

};
void tcpClient::handle_read_message(const boost::system::error_code & error) {

	if (!error && !m_closing) {

		m_scroll.append("server replied: " + m_message.m_body);

	} else {

		m_scroll.append("an error message has been sent by the server: ");
		m_scroll.append(error.message());

	}
};

void tcpClient::handle_write_message(const boost::system::error_code & error) {

	if (!error && !m_closing) {

//		m_connection->async_write(m_message,
//			boost::bind(&tcpClient::handle_write_message,
//				shared_from_this(),
//				boost::asio::placeholders::error));

	}
};

void tcpClient::check_deadline() {

	if (m_connected && !m_closing) {

		if (m_deadline.expires_at() <= boost::asio::deadline_timer::traits_type::now()) {

			m_connection->socket().close();
			m_deadline.expires_at(boost::posix_time::pos_infin);

		}

		// put the deadline back to sleep
		m_deadline.async_wait(boost::bind(&tcpClient::check_deadline, this));

	}
}

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
