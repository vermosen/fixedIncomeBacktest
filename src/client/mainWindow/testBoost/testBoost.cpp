/*
 * controlBox.cpp
 *
 *  Created on: May 14, 2015
 *      Author: vermosen
 */

#include <client/mainWindow/testBoost/testBoost.hpp>

testBoost::testBoost(clientSettings& settings,
					 scrolledLogWindow& logger	)
	: m_ios(), m_logger(logger), m_settings(settings) {

	m_connectButton 	= Gtk::manage(new Gtk::Button("connect to the server"			));
	m_messageButton 	= Gtk::manage(new Gtk::Button("send a message to the server"	));
	m_databaseButton 	= Gtk::manage(new Gtk::Button("send database login information"	));
	m_disconnectButton 	= Gtk::manage(new Gtk::Button("disconnect to the database"		));

	m_connectButton->signal_clicked().connect(sigc::mem_fun(this,
		&testBoost::on_connectButton_clicked));

	m_messageButton->signal_clicked().connect(sigc::mem_fun(this,
		&testBoost::on_messageButton_clicked));

	m_databaseButton->signal_clicked().connect(sigc::mem_fun(this,
		&testBoost::on_databaseButton_clicked));

	m_disconnectButton->signal_clicked().connect(sigc::mem_fun(this,
		&testBoost::on_disconnectButton_clicked));

	pack_start(*m_connectButton		, false, false);								// adds the buttons to the current page
	pack_start(*m_messageButton		, false, false);
	pack_start(*m_databaseButton	, false, false);
	pack_start(*m_disconnectButton	, false, false);

	//boost::asio::deadline_timer t(m_ios, boost::posix_time::seconds(1));			// timer...
	m_client = boost::shared_ptr<tcpClient>(										// create the tcp client
		new tcpClient(m_ios, m_logger));

	m_thread = boost::shared_ptr<boost::thread>(									// launch io_service.run()
		new boost::thread(boost::bind(
			&boost::asio::io_service::run,
			boost::ref(m_ios))));

}

void testBoost::on_connectButton_clicked() {

	std::string ip 		= m_settings.server_ip		();							// loads the settings
	std::string port 	= m_settings.server_port	();
	m_logger.append("attempting to connect to the server " + ip + ":" + port);

	tcp::endpoint endpoint(	boost::asio::ip::address::from_string(ip)	,		// create the end point
							boost::lexical_cast<int>(port)				);

	try {

		m_client->connect(endpoint);											// connecting to the endpoint

	} catch (std::exception& e) {

		m_logger.append("error: " + std::string(e.what()));

	}
}

void testBoost::on_messageButton_clicked() {

	try {

		message m("Hello...");													// message
		m_logger.append("sending message: " + m.m_body);						// information
		m_client->deliver(m);

	} catch (std::exception& e) {

		m_logger.append("error: " + std::string(e.what()));

	}
}

void testBoost::on_databaseButton_clicked() {

	m_logger.append("database connection test: ");
	m_logger.append("ip: " 		+ m_settings.sql_login().ip		());
	m_logger.append("port: " 	+ m_settings.sql_login().port	());
	m_logger.append("user: " 	+ m_settings.sql_login().user	());
	m_logger.append("pwd: " 	+ m_settings.sql_login().pwd	());
	m_logger.append("schema: " 	+ m_settings.sql_login().schema	());

	try {

		m_client->deliver(m_settings.sql_login());

	} catch (std::exception& e) {

		m_logger.append("error: " + std::string(e.what()));

	}
}

void testBoost::on_disconnectButton_clicked() {

	m_logger.append("attempting to disconnect from the server..");

	try {


	} catch (std::exception& e) {

		m_logger.append("error: " + std::string(e.what()));

	}
}
