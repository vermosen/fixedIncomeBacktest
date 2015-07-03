/*
 * controlBox.hpp
 *
 *  Created on: May 14, 2015
 *      Author: vermosen
 */

#ifndef TESTBOOST_HPP_
#define TESTBOOST_HPP_

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/asio.hpp>

#include <gtkmm.h>

#include <client/clientSettings/clientSettings.hpp>
#include <client/mainWindow/scrolledLogWindow/scrolledLogWindow.hpp>
#include <client/tcpClient/tcpClient.hpp>

class testBoost : public Gtk::HBox {

public:

	testBoost(clientSettings&, scrolledLogWindow&);
	virtual ~testBoost() {};

protected:
	void on_connectButton_clicked	();						// Signal handlers:
	void on_messageButton_clicked	();
	void on_databaseButton_clicked	();
	void on_disconnectButton_clicked();

	// shared components
	scrolledLogWindow& 	m_logger	;						// logger
	clientSettings& 	m_settings	;						// settings

	boost::asio::io_service					m_ios		;	// asio components
	boost::shared_ptr<tcpClient> 			m_client	;
	boost::shared_ptr<boost::thread> 		m_thread	;

	// Gtk components
	Gtk::Button * m_connectButton	;						// connect to the server
	Gtk::Button * m_messageButton	;						// test messaging
	Gtk::Button * m_databaseButton	;						// connect to the database
	Gtk::Button * m_disconnectButton;						// disconnect from the server

};

#endif /* TESTBOOST_HPP_ */
