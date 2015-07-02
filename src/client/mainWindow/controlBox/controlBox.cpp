/*
 * controlBox.cpp
 *
 *  Created on: May 14, 2015
 *      Author: vermosen
 */

#include <client/mainWindow/controlBox/controlBox.hpp>

controlBox::controlBox(	boost::shared_ptr<clientSettings> 		settings,
						boost::shared_ptr<scrolledLogWindow> 	logger	,
						int width, int height)
	: m_settings(settings), m_logger(logger) {

	m_boxMain = Gtk::manage(new Gtk::HBox(Gtk::ORIENTATION_HORIZONTAL, 10));
	m_boxMain->set_border_width(border_size);

	m_frame1 = Gtk::manage(new Gtk::Frame());	// set the frames
	m_frame2 = Gtk::manage(new Gtk::Frame());
	m_frame3 = Gtk::manage(new Gtk::Frame());

	m_frame1->set_label("server ip configuration");
	m_frame2->set_label("database management");
	m_frame3->set_label("interactive broker");

	m_frame_box1 = Gtk::manage(new Gtk::VBox());
	m_frame_box2 = Gtk::manage(new Gtk::VBox());
	m_frame_box3 = Gtk::manage(new Gtk::VBox());

	width -= (border_size * 2);					// substract border size

	m_frame1->set_size_request(width / 3);
	m_frame2->set_size_request(width / 3);
	m_frame3->set_size_request(width / 3);

	// create the entry boxes
	m_serverIp_entry	= Gtk::manage(new entryBox("server ip"			));
	m_serverPort_entry 	= Gtk::manage(new entryBox("server port"		));
	m_dbIp_entry 		= Gtk::manage(new entryBox("database ip"		));
	m_dbPort_entry 		= Gtk::manage(new entryBox("database port"		));
	m_dbUser_entry 		= Gtk::manage(new entryBox("database user"		));
	m_dbPwd_entry 		= Gtk::manage(new entryBox("database password"	));
	m_dbSchema_entry 	= Gtk::manage(new entryBox("database schema"	));

	m_serverIp_entry	->set_size_request(width / 3, 20);
	m_serverPort_entry	->set_size_request(width / 3, 20);
	m_dbIp_entry		->set_size_request(width / 3, 20);
	m_dbPort_entry 		->set_size_request(width / 3, 20);
	m_dbUser_entry		->set_size_request(width / 3, 20);
	m_dbPwd_entry		->set_size_request(width / 3, 20);
	m_dbSchema_entry	->set_size_request(width / 3, 20);

	// add the widgets
	m_frame_box1->pack_start(*m_serverIp_entry	, false, false);
	m_frame_box1->pack_start(*m_serverPort_entry, false, false);
	m_frame_box2->pack_start(*m_dbIp_entry		, false, false);
	m_frame_box2->pack_start(*m_dbPort_entry	, false, false);
	m_frame_box2->pack_start(*m_dbUser_entry	, false, false);
	m_frame_box2->pack_start(*m_dbPwd_entry		, false, false);
	m_frame_box2->pack_start(*m_dbSchema_entry	, false, false);

	m_frame1->add(* m_frame_box1);				// HBox
	m_frame2->add(* m_frame_box2);
	m_frame3->add(* m_frame_box3);

	m_boxMain->add(* m_frame1);					// main box
	m_boxMain->add(* m_frame2);
	m_boxMain->add(* m_frame3);

	this->add(* m_boxMain);						// window

	// entry box bindings
	m_serverIp_entry	->entry().signal_focus_out_event().connect(sigc::mem_fun(this,
		&controlBox::on_serverIp_focus_out	));
	m_serverPort_entry	->entry().signal_focus_out_event().connect(sigc::mem_fun(this,
		&controlBox::on_serverPort_focus_out));
	m_dbIp_entry		->entry().signal_focus_out_event().connect(sigc::mem_fun(this,
		&controlBox::on_dbIp_focus_out		));
	m_dbPort_entry		->entry().signal_focus_out_event().connect(sigc::mem_fun(this,
		&controlBox::on_dbPort_focus_out	));
	m_dbUser_entry		->entry().signal_focus_out_event().connect(sigc::mem_fun(this,
		&controlBox::on_dbUser_focus_out	));
	m_dbPwd_entry		->entry().signal_focus_out_event().connect(sigc::mem_fun(this,
		&controlBox::on_dbPwd_focus_out		));
	m_dbSchema_entry	->entry().signal_focus_out_event().connect(sigc::mem_fun(this,
		&controlBox::on_dbSchema_focus_out	));

	fillFromSettings();							// fill the default values

}

void controlBox::fillFromSettings() {

	m_serverIp_entry	->entry().set_text(m_settings->server_ip			());
	m_serverPort_entry	->entry().set_text(m_settings->server_port			());
	m_dbIp_entry		->entry().set_text(m_settings->sql_login().ip		());
	m_dbPort_entry		->entry().set_text(m_settings->sql_login().port		());
	m_dbUser_entry		->entry().set_text(m_settings->sql_login().user		());
	m_dbPwd_entry		->entry().set_text(m_settings->sql_login().pwd		());
	m_dbSchema_entry	->entry().set_text(m_settings->sql_login().schema	());

}

bool controlBox::on_serverIp_focus_out (GdkEventFocus* event) {

	std::string s = m_serverIp_entry->entry().get_text();
	if (s != "") m_settings->server_ip(s);
	return true;

}

bool controlBox::on_serverPort_focus_out (GdkEventFocus* event) {

	std::string s = m_serverPort_entry->entry().get_text();
	if (s != "") m_settings->server_port(s);
	return true;

}

bool controlBox::on_dbIp_focus_out (GdkEventFocus* event) {

	std::string s = m_dbIp_entry->entry().get_text();
	if (s != "") m_settings->sql_login().ip(s);
	return true;

}

bool controlBox::on_dbPort_focus_out (GdkEventFocus* event) {

	std::string s = m_dbPort_entry->entry().get_text();
	if (s != "") m_settings->sql_login().port(s);
	return true;

}

bool controlBox::on_dbUser_focus_out (GdkEventFocus* event) {

	std::string s = m_dbUser_entry->entry().get_text();
	if (s != "") m_settings->sql_login().user(s);
	return true;

}

bool controlBox::on_dbPwd_focus_out (GdkEventFocus* event) {

	std::string s = m_dbPwd_entry->entry().get_text();
	if (s != "") m_settings->db_pwd(s);
	return true;

}

bool controlBox::on_dbSchema_focus_out (GdkEventFocus* event) {

	std::string s = m_dbSchema_entry->entry().get_text();
	if (s != "") m_settings->sql_login().schema(s);
	return true;

}
