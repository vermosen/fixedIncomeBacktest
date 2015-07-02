/*
 * clientSettings.cpp
 *
 *  Created on: Jun 21, 2015
 *      Author: vermosen
 */

#include "clientSettings.hpp"

clientSettings::clientSettings()
	: m_server_ip	(DEFAULT_SERVER_IP	),
	  m_server_port	(DEFAULT_SERVER_PORT) {

	m_sql_conn = {
					DEFAULT_DB_IP,
					DEFAULT_DB_PORT,
					DEFAULT_DB_USER,
					DEFAULT_DB_PWD,
					DEFAULT_DB_SCHEMA
	};

}

clientSettings::~clientSettings() {}

std::string clientSettings::server_ip() const {

	boost::lock_guard<boost::mutex> lock(mu_server_ip);
	return m_server_ip;

};

void clientSettings::server_ip(const std::string & str) {


	boost::lock_guard<boost::mutex> lock(mu_server_ip);

	if (str != "") m_server_ip = str;						// TODO: if is valid ip...

};

std::string clientSettings::server_port() const {

	boost::lock_guard<boost::mutex> lock(mu_server_port);
	return m_server_port;

};

void clientSettings::server_port(const std::string & str) {

	boost::lock_guard<boost::mutex> lock(mu_server_port);
	m_server_port = str;

};

sqlLogin clientSettings::sql_login() const {

	boost::lock_guard<boost::mutex> lock(mu_sql_conn);
	return m_sql_conn;

};

void clientSettings::db_ip(const std::string & s) {

	boost::lock_guard<boost::mutex> lock(mu_sql_conn);
	m_sql_conn.ip(s);

};

void clientSettings::db_port(const std::string & s) {

	boost::lock_guard<boost::mutex> lock(mu_sql_conn);
	m_sql_conn.port(s);

};

void clientSettings::db_user(const std::string & s) {

	boost::lock_guard<boost::mutex> lock(mu_sql_conn);
	m_sql_conn.user(s);

};

void clientSettings::db_pwd(const std::string & s) {

	boost::lock_guard<boost::mutex> lock(mu_sql_conn);
	m_sql_conn.pwd(s);

};

void clientSettings::db_schema(const std::string & s) {

	boost::lock_guard<boost::mutex> lock(mu_sql_conn);
	m_sql_conn.schema(s);

};

