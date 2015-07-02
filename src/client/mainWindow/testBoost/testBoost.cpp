/*
 * controlBox.cpp
 *
 *  Created on: May 14, 2015
 *      Author: vermosen
 */

#include <client/mainWindow/testBoost/testBoost.hpp>

testBoost::testBoost(	boost::shared_ptr<clientSettings> 		settings,
						boost::shared_ptr<scrolledLogWindow> 	logger	)
	: m_logger(logger), m_settings(settings), m_ios() {

	Gtk::Button * m_serverButton	;						// connect to the server
	Gtk::Button * m_databaseButton	;						// connect to the database

	m_serverButton 		= Gtk::manage(new Gtk::Button("connect to the server"));
	m_databaseButton 	= Gtk::manage(new Gtk::Button("connect to the database"));

	m_serverButton->signal_clicked().connect(sigc::mem_fun(this,
			&testBoost::on_server_button_clicked));

	m_databaseButton->signal_clicked().connect(sigc::mem_fun(this,
			&testBoost::on_database_button_clicked));

	pack_start(*m_serverButton	, false, false);								// adds the button to the current page
	pack_start(*m_databaseButton, false, false);

	// create and connect the client
	tcp::endpoint endpoint( boost::asio::ip::address::from_string(m_settings->server_ip()),
							boost::lexical_cast<int>(m_settings->server_port()));

	boost::asio::deadline_timer t(m_ios, boost::posix_time::seconds(1));
	m_client = boost::shared_ptr<tcpClient>(new tcpClient(m_ios, m_logger));
	m_client->connect(endpoint);

	// launch io_service.run()
	m_thread = boost::shared_ptr<boost::thread>(
		new boost::thread(boost::bind(&boost::asio::io_service::run, boost::ref(m_ios))));

}

void testBoost::on_server_button_clicked() {

	// change the label
	m_logger->append("server connection test");

	try {

		message m("Hello...");						// message
		m_logger->append("sending message: ");
		m_logger->append(m.m_body);
		m_client->deliver(m);						// deliver to the server

	} catch (std::exception& e) {

		m_logger->append(e.what());

	}
}

void testBoost::on_database_button_clicked() {

	m_logger->append("database connection test: ");
	m_logger->append("ip: " 	+ m_settings->sql_login().ip	());
	m_logger->append("port: " 	+ m_settings->sql_login().port	());
	m_logger->append("user: " 	+ m_settings->sql_login().user	());
	m_logger->append("pwd: " 	+ m_settings->sql_login().pwd	());
	m_logger->append("schema: " + m_settings->sql_login().schema());

	try {

		m_client->deliver(m_settings->sql_login());

	} catch (std::exception& e) {

		m_logger->append(e.what());

	}
}
