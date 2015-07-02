/*
 * mainWindow.hpp
 *
 *  Created on: May 12, 2015
 *      Author: vermosen
 */

#ifndef MAINWINDOW_HPP_
#define MAINWINDOW_HPP_

#include <gtkmm.h>

#include <client/clientSettings/clientSettings.hpp>
#include <client/mainWindow/scrolledLogWindow/scrolledLogWindow.hpp>
#include <client/mainWindow/mainNotebook/mainNotebook.hpp>

class mainWindow : public Gtk::Window {

public:
	mainWindow(int, int);
	virtual ~mainWindow() {};

	void on_log(const Glib::ustring &);						// log message

protected:

	// shared objects
	boost::shared_ptr<clientSettings> 		m_settings	;	// the application settings
	boost::shared_ptr<scrolledLogWindow> 	m_logger	;	// the logger object

	Gtk::Paned 		* m_paned	;							// the main window paned
	Gtk::VBox 	 	* m_mainBox	;							// the main box
	Gtk::Notebook 	* m_notebook;							// the main notebook

	// the progress bar elements
	Gtk::HBox 			* m_progressBox		;
	Gtk::Label 			* m_progressLabel	;
	Gtk::ProgressBar 	* m_progressBar		;

	int m_height; int m_width;								// height, width

};

#endif /* MAINWINDOW_HPP_ */
