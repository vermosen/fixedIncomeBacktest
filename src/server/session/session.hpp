/*
 * session.hpp
 *
 *  Created on: May 23, 2015
 *      Author: vermosen
 */

#ifndef SESSION_HPP_
#define SESSION_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/asio/placeholders.hpp>

// mysql include
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <shared/tcpConnection/tcpConnection.hpp>
#include <shared/message/message.hpp>
#include <shared/sqlLogin/sqlLogin.hpp>

#include <server/tcpServer/tcpServer.hpp>
#include <server/recordset/instrumentRecordset/instrumentRecordset.hpp>

using boost::asio::ip::tcp;

class tcpServer;

// represent a connection session from a client
class session : public boost::enable_shared_from_this<session> {

public:

	~session() {};

	// factory
	static boost::shared_ptr<session> create(
		boost::shared_ptr<tcpConnection> connection_, tcpServer & server_);

	void deliver(const message & msg);				// delivers a log message

private:
	session(boost::shared_ptr<tcpConnection> connection, tcpServer & server_);

	void wait_for_database_login();					// the methods to wait for specific types
	void wait_for_msg			();

	void handle_read_msg		(const boost::system::error_code& error);
	void handle_write_msg		(const boost::system::error_code& error);
	void handle_sql_identifier	(const boost::system::error_code& error);

	void databaseConnect();
	void databaseRequest();

	boost::shared_ptr<tcpConnection> m_connection;

	tcpServer&		m_server	;					// the server
	bool			is_leaving	;					// session is disconnecting
	message			m_message	;					// the current message
	sqlLogin		m_dbLogin	;					// the sql identifiers

	sql::Connection * m_sqlConn	;					// the mySql connection

};

#endif /* SESSION_HPP_ */
