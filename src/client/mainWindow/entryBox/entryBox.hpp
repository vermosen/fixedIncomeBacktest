/*
 * entryBox.hpp
 *
 *  Created on: Jun 21, 2015
 *      Author: vermosen
 */

#ifndef ENTRYBOX_HPP_
#define ENTRYBOX_HPP_

#include <gtkmm.h>

class entryBox : public Gtk::Box {

public:
	entryBox(const std::string & str = "");
	virtual ~entryBox() {};

	Gtk::Entry& entry() { return m_entry; };

protected:
	Gtk::Entry m_entry;
	Gtk::Label m_label;

};

#endif /* ENTRYBOX_HPP_ */
