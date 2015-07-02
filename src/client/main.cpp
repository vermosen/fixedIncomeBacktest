//============================================================================
// Name        : yieldCurveAnalyserClient.cpp
// Author      : Jean-Mathieu Vermosen
// Version     :
// Copyright   : all rights reserved
// Description : yield curve analysis tool in C++, Ansi-style
//============================================================================

#include <gtkmm.h>

#include <client/mainWindow/mainWindow.hpp>

int main (int argc, char *argv[]) {

	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.yield.curve.analyser.client");

	mainWindow mainWin(1200, 1800);

	//Shows the window and returns when it is closed.
	return app->run(mainWin);

}
