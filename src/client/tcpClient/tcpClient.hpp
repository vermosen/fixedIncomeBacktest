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

#include <shared/tcpConnection/tcpConnection.hpp>
#include <shared/sqlLogin/sqlLogin.hpp>
#include <shared/message/message.hpp>
#include <client/mainWindow/scrolledLogWindow/scrolledLogWindow.hpp>

class tcpClient : public boost::enable_shared_from_this<tcpClient> {

public:
	tcpClient(boost::asio::io_service&, boost::shared_ptr<scrolledLogWindow>);

	void connect(boost::asio::ip::tcp::endpoint&);

	void deliver(const message&	);									// the deliver methods
	void deliver(const sqlLogin&);

private:
	// callbacks
	void handle_connect			(const boost::system::error_code& error);
	void handle_read			(const boost::system::error_code& error);
	void handle_write_message	(const boost::system::error_code& error);
	void handle_write_sql_login	(const boost::system::error_code& error);

	void read();

	bool	m_closing	;											// booleans
	bool	m_connected	;

	boost::asio::io_service&			m_ios		;				// asio components
	boost::asio::deadline_timer 		m_timer		;
	boost::shared_ptr<tcpConnection> 	m_connection;

	boost::shared_ptr<scrolledLogWindow> m_scroll	;				// shared objects

	message								m_message	;				// message returned
	sqlLogin							m_sqlLogin	;

};
#endif /* TCPCLIENT_HPP_ */
