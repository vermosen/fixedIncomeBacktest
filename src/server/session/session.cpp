/*
 * session.cpp
 *
 *  Created on: May 26, 2015
 *      Author: vermosen
 */

#include <server/session/session.hpp>

boost::shared_ptr<session> session::create(
	boost::shared_ptr<tcpConnection> connection_,
	tcpServer & server_) {

	boost::shared_ptr<session> m_session(new session(connection_, server_));

	m_session->wait_for_msg();
	//m_session->wait_for_database_login();

	return m_session;

}

void session::deliver(const message& msg) {

	m_connection->async_write(msg,
		boost::bind(&session::handle_write_msg, shared_from_this(),
		boost::asio::placeholders::error));

	wait_for_msg();

}

session::session(boost::shared_ptr<tcpConnection> connection_, tcpServer & server_)
	: m_connection	(connection_),
	  m_server		(server_	) {

	is_leaving = false;

}

void session::wait_for_database_login() {

	m_connection->async_read(
		m_dbLogin,
		boost::bind(
			&session::handle_sql_identifier,
			shared_from_this(),
			boost::asio::placeholders::error));

}

void session::wait_for_msg() {									// wait for incoming message

	m_connection->async_read(									// wait for data
		m_message,
		boost::bind(
			&session::handle_read_msg,
			shared_from_this(),
			boost::asio::placeholders::error));
}

void session::handle_read_msg(const boost::system::error_code &error) {

	if (!error) {

		// deliver the request
		std::cout
			<< "message received: "
			<< std::endl
			<< m_message.m_body
			<< std::endl;

		if (m_message.m_body == "Hello...") deliver(message("...World!"));

		m_message.reset();
		wait_for_msg();											// wait for data from heres
		wait_for_database_login();

	} else {

		std::cout
			<< error
			<< std::endl;

		if (!is_leaving) {

			is_leaving = true;
			// close the session

		}
	}
}

void session::handle_write_msg(const boost::system::error_code & error) {

	if (error && (!is_leaving) ) {

		is_leaving = true;										// close the session

	}
}

void session::handle_sql_identifier(const boost::system::error_code& error) {

	if (error && (!is_leaving) ) {

		is_leaving = true;										// close the session


	} else {

		wait_for_msg();

	}
}

void session::databaseConnect() {

	try {

		sql::Driver * driver = get_driver_instance();

		// TODO: get those informations from the client
		m_sqlConn = driver->connect(
			m_dbLogin.ip	() + ":" + m_dbLogin.port(),
			m_dbLogin.user	(),
			m_dbLogin.pwd	());

		/* Connect to the MySQL test database */
		m_sqlConn->setSchema(m_dbLogin.schema());

		deliver(message("connection to the database successful !"));

	} catch (sql::SQLException & e) {

		std::cout << "sql error: " 	<< e.what			() 	<< std::endl;
		std::cout << "sql code: " 	<< e.getErrorCode	() 	<< std::endl;
		std::cout << "sql state: " 	<< e.getSQLState	() 	<< std::endl;

	} catch (std::exception & e) {

		std::cout << "An error occurred: " 	<< e.what	() 	<< std::endl;

	} catch (...) {

		std::cout << "An unknown error occurred..." 		<< std::endl;

	}
}

void session::databaseRequest() {

	// TODO: handle the db connection
	try {

		sql::Statement 	* stmt	;
		sql::ResultSet 	* res	;

		stmt = m_sqlConn->createStatement();
		res = stmt->executeQuery("SELECT * FROM table_instrument");

		// reserve the number of rows
		std::vector<std::string> names; names.reserve(res->rowsCount());

		while (res->next())
			names.push_back(res->getString("instrument_isin"));

		for (auto It = names.cbegin(); It != names.cend(); It++) {

			deliver(message("instrument: " + *It));

		}

		delete res	;
		delete stmt	;

	} catch (sql::SQLException & e) {

		std::cout << "sql error: " 	<< e.what			() << std::endl;
		std::cout << "sql code: " 	<< e.getErrorCode	() << std::endl;
		std::cout << "sql state: " 	<< e.getSQLState	() << std::endl;

	}

	deliver(message("connection to the database succeeded"));

}

