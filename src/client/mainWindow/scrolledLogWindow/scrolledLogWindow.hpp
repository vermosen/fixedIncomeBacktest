/*
 * scrolledLogWindow.hpp
 *
 *  Created on: May 13, 2015
 *      Author: vermosen
 */

#ifndef SCROLLEDLOGWINDOW_HPP_
#define SCROLLEDLOGWINDOW_HPP_

#include <gtkmm.h>

class scrolledLogWindow : public Gtk::ScrolledWindow {

public:
	scrolledLogWindow(const Glib::ustring & str = "log");
	virtual ~scrolledLogWindow();

	class ModelColumns : public Gtk::TreeModel::ColumnRecord {

	public:

		ModelColumns() { add(m_col_text); }

		Gtk::TreeModelColumn<Glib::ustring> m_col_text;

};

	ModelColumns m_Columns;

	//TODO: add operator <<
	void append(const Glib::ustring &);

protected:
	Glib::RefPtr<Gtk::ListStore> m_refListStore; //The Tree Model.
	Gtk::TreeView m_TreeView; //The Tree View.

};

#endif /* SCROLLEDLOGWINDOW_HPP_ */
