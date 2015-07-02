/*
 * controlBox.hpp
 *
 *  Created on: May 14, 2015
 *      Author: vermosen
 */

#ifndef TESTBOOST_HPP_
#define TESTBOOST_HPP_

#include <gtkmm.h>

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/asio.hpp>

#include <client/clientSettings/clientSettings.hpp>
#include <client/mainWindow/scrolledLogWindow/scrolledLogWindow.hpp>
#include <client/tcpClient/tcpClient.hpp>

class testBoost : public Gtk::HBox {

public:

	testBoost(boost::shared_ptr<clientSettings>, boost::shared_ptr<scrolledLogWindow>);
	virtual ~testBoost() {};

protected:
	void on_server_button_clicked	();						// Signal handlers:
	void on_database_button_clicked	();

	// shared components
	boost::shared_ptr<scrolledLogWindow> 	m_logger	;	// logger
	boost::shared_ptr<clientSettings> 		m_settings	;	// settings
	boost::asio::io_service					m_ios		;	// asio components
	boost::shared_ptr<tcpClient> 			m_client	;
	boost::shared_ptr<boost::thread> 		m_thread	;

	// Gtk components
	Gtk::Button * m_serverButton	;						// connect to the server
	Gtk::Button * m_databaseButton	;						// connect to the database

};

#endif /* TESTBOOST_HPP_ */
