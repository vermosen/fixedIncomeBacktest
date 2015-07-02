/*
 * scrolledLogWindow.cpp
 *
 *  Created on: May 13, 2015
 *      Author: vermosen
 */

#include "scrolledLogWindow.hpp"

scrolledLogWindow::scrolledLogWindow(const Glib::ustring & title) {

	/* Create a new scrolled window, with scrollbars only if needed */
	set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	add(m_TreeView);

	/* create list store */
	m_refListStore = Gtk::ListStore::create(m_Columns);
	m_TreeView.set_model(m_refListStore);

	//Add the unique column with title
	m_TreeView.append_column(title, m_Columns.m_col_text);

	std::ostringstream text;
	text << "welcome to the yield curve analyser...";
	Gtk::TreeModel::Row row = *(m_refListStore->append());
	row[m_Columns.m_col_text] = text.str();
	show_all_children();

}

scrolledLogWindow::~scrolledLogWindow() {}

void scrolledLogWindow::append(const Glib::ustring & str) {

	std::ostringstream text; text << str;
	Gtk::TreeModel::Row row = *(m_refListStore->append());
	row[m_Columns.m_col_text] = text.str();
	show_all_children();

};
