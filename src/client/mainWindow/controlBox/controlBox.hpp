/*
 * controlBox.hpp
 *
 *  Created on: May 14, 2015
 *      Author: vermosen
 */

#ifndef CONTROLBOX_HPP_
#define CONTROLBOX_HPP_

#include <regex>								// stl regex

#include <boost/shared_ptr.hpp>

#include <gtkmm.h>

#include <client/clientSettings/clientSettings.hpp>
#include <client/mainWindow/scrolledLogWindow/scrolledLogWindow.hpp>
#include <client/mainWindow/entryBox/entryBox.hpp>

class controlBox: public Gtk::HBox {

public:

	controlBox(boost::shared_ptr<clientSettings>, boost::shared_ptr<scrolledLogWindow> logger, int, int);
	virtual ~controlBox() {};

protected:

	bool on_serverIp_focus_out	(GdkEventFocus*);		// events
	bool on_serverPort_focus_out(GdkEventFocus*);
	bool on_dbPort_focus_out	(GdkEventFocus*);
	bool on_dbIp_focus_out		(GdkEventFocus*);
	bool on_dbUser_focus_out	(GdkEventFocus*);
	bool on_dbPwd_focus_out		(GdkEventFocus*);
	bool on_dbSchema_focus_out	(GdkEventFocus*);

	// the shared objects
	boost::shared_ptr<clientSettings> 		m_settings	;
	boost::shared_ptr<scrolledLogWindow> 	m_logger	;

	// Gtk components
	Gtk::HBox * m_boxMain;								// the main box

	Gtk::Frame * m_frame1; Gtk::VBox * m_frame_box1;	// 3 frames and associated boxes
	Gtk::Frame * m_frame2; Gtk::VBox * m_frame_box2;
	Gtk::Frame * m_frame3; Gtk::VBox * m_frame_box3;

	entryBox * m_serverIp_entry		;					// entry boxes
	entryBox * m_serverPort_entry	;
	entryBox * m_dbIp_entry			;
	entryBox * m_dbPort_entry		;
	entryBox * m_dbUser_entry		;
	entryBox * m_dbPwd_entry		;
	entryBox * m_dbSchema_entry		;

	const int border_size = 10;							// the border size

private:
	void fillFromSettings();							// fills the controls with the setting

};

#endif /* CONTROLBOX_HPP_ */
