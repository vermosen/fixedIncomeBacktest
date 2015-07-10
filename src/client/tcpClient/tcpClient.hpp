/*
 * tcpClient.hpp
 *
 *  Created on: May 22, 2015
 *      Author: vermosen
 */

#ifndef TCPCLIENT_HPP_
#define TCPCLIENT_HPP_

#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>

#include <shared/tcpConnection/tcpConnection.hpp>
#include <shared/sqlLogin/sqlLogin.hpp>
#include <shared/message/message.hpp>
#include <client/mainWindow/scrolledLogWindow/scrolledLogWindow.hpp>

class tcpClient : public boost::enable_shared_from_this<tcpClient> {

public:

	static boost::shared_ptr<tcpClient> create(						// factory
		boost::asio::io_service&, scrolledLogWindow&);

	void connect	(boost::asio::ip::tcp::endpoint&);				// connect to the endpoint
	void disconnect	();

	void deliver(const message&	);									// the deliver methods
	//void deliver(const sqlLogin&);

private:

	// thread management
	void add_service(boost::asio::io_service & ios) {
		boost::asio::io_service::work work(ios);
	}

	void join_services() {
		m_threads.join_all();
	}

	void check_deadline();											// check the deadline

	// callbacks
	void handle_connect			(const boost::system::error_code& error);
	void handle_read_message	(const boost::system::error_code& error);
	void handle_write_message	(const boost::system::error_code& error);
	//void handle_write_sql_login	(const boost::system::error_code& error);



	void read_message();

	bool	m_closing	;											// is closing ?
	bool	m_connected	;											// is connected ?

	boost::asio::io_service&			m_ios		;				// io_service
	boost::asio::io_service::work		m_work		;				// prevent the io_service to stop
	boost::asio::deadline_timer 		m_deadline	;				// deadline timer

	boost::shared_ptr<tcpConnection> 	m_connection;				// shared objects
	boost::thread_group					m_threads	;				// a (pool of) threads to capture the io_service.run()

	scrolledLogWindow& m_scroll;

	message								m_message	;				// message i/o
	//sqlLogin							m_sqlLogin	;

	tcpClient(boost::asio::io_service&, scrolledLogWindow&);

};
#endif /* TCPCLIENT_HPP_ */
