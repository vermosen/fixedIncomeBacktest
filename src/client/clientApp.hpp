/*
 * clientApp.hpp
 *
 *  Created on: Jun 21, 2015
 *      Author: vermosen
 */

#ifndef CLIENTAPP_HPP_
#define CLIENTAPP_HPP_

#include <gtkmm/application.h>

class clientApp: public Gtk::Application {
public:
	clientApp();
	virtual ~clientApp();
};

#endif /* CLIENTAPP_HPP_ */
