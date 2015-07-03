/*
 * mainWindow.cpp
 *
 *  Created on: May 12, 2015
 *  Author: vermosen
 */

#include <client/mainWindow/mainWindow.hpp>

mainWindow::mainWindow(int height, int width)
	: m_settings	()							,
	  m_logger		("Applications messages")	,
	  m_height		(height)					,
	  m_width		(width)
{

	// main objects
	m_paned 		= Gtk::manage(new Gtk::Paned	(Gtk::ORIENTATION_VERTICAL				));
	m_notebook 		= Gtk::manage(new mainNotebook	(m_settings, m_logger, m_height, m_width));
	m_mainBox 		= Gtk::manage(new Gtk::VBox		(										));

	// set windows properties
	this->set_size_request(m_width, m_height);	// window size
	this->set_resizable(false);					// resizable ?
	this->set_title("yield Curve Analyser");	// title
	this->set_border_width(10);					// set border

	// the progress bar
	m_progressBox	= Gtk::manage(new Gtk::HBox			(			));
	m_progressBar 	= Gtk::manage(new Gtk::ProgressBar	(			));
	m_progressLabel = Gtk::manage(new Gtk::Label		("progress"	));

	m_progressBox->add(* m_progressLabel);
	m_progressBox->add(* m_progressBar);

	m_progressBar->set_hexpand(false);
	m_progressBar->set_text("");
	m_progressBar->set_show_text();

	// the main VBox
	this->add(*m_mainBox);

	// the main paned properties
	m_mainBox->add(* m_paned);							// create the main paned
	m_mainBox->pack_start(* m_progressBox, Gtk::PACK_SHRINK);

	// the paned component
	m_paned->add			(*m_notebook);				// create the frame on top
	m_paned->add			(m_logger	);				// create the log list
	m_paned->set_position	(1000		);

	Gtk::Window::show_all_children(true);				// show all the elements

}

void mainWindow::on_log(const Glib::ustring & message) {

	m_logger.append(message);

}

