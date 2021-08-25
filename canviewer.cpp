//============================================================================
// Name        : canviewer.cpp
// Author      : Tim Lucas Sabelmann
// Version     :
// Copyright   : E-Cap Mobility GmbH
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <sstream>
#include <inttypes.h>

#include "gtkmm/MainWindow.hpp"


using namespace std;

int main(int argc, char *argv[])
{
	try
	{
		  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
		  Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("window.glade");

		  gtkmm::MainWindow *window = nullptr;
		  builder->get_widget_derived("main_window", window);

		  app->run(*window);

	}

	catch(std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	catch(int e)
	{
		std::cerr << e << std::endl;
	}

//auto items = Glib::RefPtr<Gtk::TreeModel>::cast_dynamic(builder->get_object("treestore1"));
}
