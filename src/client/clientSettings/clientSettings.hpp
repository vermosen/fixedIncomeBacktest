/*
 * clientSettings.hpp
 *
 *  Created on: Jun 21, 2015
 *      Author: vermosen
 */

#ifndef CLIENTSETTINGS_HPP_
#define CLIENTSETTINGS_HPP_

#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>

#include <shared/sqlLogin/sqlLogin.hpp>

// the default app settings
#define DEFAULT_SERVER_IP 		"127.0.0.1"
#define DEFAULT_SERVER_PORT 	"7171"
#define DEFAULT_DB_IP 			"127.0.0.1"
#define DEFAULT_DB_PORT 		"3306"
#define DEFAULT_DB_USER			"TESTUSER"
#define DEFAULT_DB_PWD			"TEST01"
#define DEFAULT_DB_SCHEMA		"fixedIncomeBackTest"

class clientSettings : public boost::noncopyable {

public:
	clientSettings();
	virtual ~clientSettings();

	std::string 	server_ip	() const;					// getters
	std::string 	server_port	() const;
	sqlLogin 		sql_login	() const;

	void server_ip	(const std::string &	);				// setters
	void server_port(const std::string &	);
	void db_ip		(const std::string &	);
	void db_port	(const std::string &	);
	void db_user	(const std::string &	);
	void db_pwd		(const std::string &	);
	void db_schema	(const std::string &	);

private:
	std::string	m_server_ip		;	mutable boost::mutex mu_server_ip	;
	std::string	m_server_port	;	mutable boost::mutex mu_server_port	;
	sqlLogin 	m_sql_conn		;	mutable boost::mutex mu_sql_conn	;

};

#endif /* CLIENTSETTINGS_HPP_ */
