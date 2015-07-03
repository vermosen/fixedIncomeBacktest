/*
 * mainNotebook.cpp
 *
 *  Created on: Jun 21, 2015
 *      Author: vermosen
 */

#include "mainNotebook.hpp"

mainNotebook::mainNotebook(
	clientSettings& settings	,
	scrolledLogWindow& logger	,
	int height, int width						)

	: m_settings(settings	),
	  m_logger	(logger		),
	  m_height	(height		),
	  m_width	(width		) {

	// labels
	m_label1 = Gtk::manage(new Gtk::Label("control panel"		));
	m_label2 = Gtk::manage(new Gtk::Label("data visualization"	));
	m_label3 = Gtk::manage(new Gtk::Label("model selection"		));
	m_label4 = Gtk::manage(new Gtk::Label("boost test"			));

	// boxes
	m_box1 = Gtk::manage(new controlBox	( m_settings, m_logger, m_height, m_width	));
	m_box2 = Gtk::manage(new Gtk::HBox	(											));
	m_box3 = Gtk::manage(new Gtk::HBox	(											));
	m_box4 = Gtk::manage(new testBoost	( m_settings, m_logger						));

	// notebook pages
	append_page(*m_box1, *m_label1);
	append_page(*m_box2, *m_label2);
	append_page(*m_box3, *m_label3);
	append_page(*m_box4, *m_label4);

}

mainNotebook::~mainNotebook() {}

