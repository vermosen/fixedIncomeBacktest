/*
 * mainNotebook.hpp
 *
 *  Created on: Jun 21, 2015
 *      Author: vermosen
 */

#ifndef MAINNOTEBOOK_HPP_
#define MAINNOTEBOOK_HPP_

#include <gtkmm.h>

#include <client/clientSettings/clientSettings.hpp>
#include <client/mainWindow/scrolledLogWindow/scrolledLogWindow.hpp>
#include <client/mainWindow/controlBox/controlBox.hpp>
#include <client/mainWindow/testBoost/testBoost.hpp>

class mainNotebook : public Gtk::Notebook {

public:
	mainNotebook(
		clientSettings&,
		scrolledLogWindow&,
		int, int);

	virtual ~mainNotebook();

protected:

	// shared objects
	scrolledLogWindow& 	m_logger	;						// the logger object
	clientSettings& 	m_settings	;						// the application settings

	Gtk::Label * m_label1, * m_label2,						// notebook labels
			   * m_label3, * m_label4;

	Gtk::HBox * m_box1, * m_box2,							// notebook boxes
			  * m_box3, * m_box4;

	int m_height; int m_width;								// height, width

};

#endif /* MAINNOTEBOOK_HPP_ */
