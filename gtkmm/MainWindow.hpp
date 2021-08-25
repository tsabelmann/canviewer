#ifndef GTKMM_MAINWINDOW_HPP_
#define GTKMM_MAINWINDOW_HPP_

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/widget.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/box.h>
#include <gtkmm/treeview.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/liststore.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/cellrendererprogress.h>
#include <gtkmm/treestore.h>
#include <gtkmm/entry.h>
#include <gtkmm.h>
#include <glib.h>

#include <map>
#include <mutex>
#include <regex>
#include <string>
#include <chrono>
#include <memory>
#include <thread>
#include <future>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <functional>
#include <shared_mutex>

#include "../can/message.h"
#include "../can/frame.h"
#include "../can/linux_socket.h"
#include "../can/json.h"

#include "../can/to_intermediate.h"
#include "../can/to_string.h"

#include "ListModel.h"
#include "TreeModel.h"

namespace gtkmm
{
	class MainWindow: public Gtk::Window
	{
	public:
		MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
		virtual ~MainWindow() = default;

		//menue functions
		void on_open_file();
		void on_open_add_file();
		void on_close_window();
		void on_open_about_dialog();

		//view functions
		void on_start_view();
		void on_stop_view();
		void on_clear_store();

		//interface functions
		void on_add_interface();
		void on_delete_interface();
		void on_refresh_interface();

		//timeout
		sigc::connection connection;
		bool on_timeout();

	protected:
		//treeview
		std::unique_ptr<Gtk::TreeView> treeview;
		std::unique_ptr<gtkmm::TreeModel> treemodel;
		Glib::RefPtr<Gtk::TreeStore> treestore;

		//listview
		std::unique_ptr<Gtk::TreeView> listview;
		std::unique_ptr<gtkmm::ListModel> listmodel;
		Glib::RefPtr<Gtk::ListStore> liststore;

		//start, stop, clear button
		std::unique_ptr<Gtk::ToolButton> start_view;
		std::unique_ptr<Gtk::ToolButton> stop_view;
		std::unique_ptr<Gtk::ToolButton> clear_store;

		//add, delete, refresh interface list and the entry
		std::unique_ptr<Gtk::Entry> interface_field;
		std::unique_ptr<Gtk::Button> add_interface;
		std::unique_ptr<Gtk::Button> delete_interface;
		std::unique_ptr<Gtk::Button> refresh_interface;		

		//menue entry
		std::unique_ptr<Gtk::ImageMenuItem> open_file;
		std::unique_ptr<Gtk::ImageMenuItem> open_add_file;
		std::unique_ptr<Gtk::ImageMenuItem> close_window;
		std::unique_ptr<Gtk::ImageMenuItem> open_about_dialog;

		//aboutdialog
		std::unique_ptr<Gtk::AboutDialog> about_dialog;

		//mutex
		std::shared_timed_mutex running_mutex;
		std::shared_timed_mutex frames_mutex;
		std::shared_timed_mutex rows_with_no_message_mutex;

		//running
		bool running;

		//frames
		using hr_clock 		= std::chrono::high_resolution_clock;
		using hr_clock_tp 	= std::chrono::high_resolution_clock::time_point;
		using tuple_t 		= std::tuple<can::frame, std::string, uint32_t, hr_clock_tp, hr_clock_tp, bool>;
		std::map<uint32_t, tuple_t> frames;

		//messages & enums
		std::map<uint32_t, can::message> messages;
		std::map<std::string, can::var_enum> enums;

		//message indexing
		std::map<uint32_t, Gtk::TreeModel::iterator> rows_with_message;
		std::map<uint32_t, Gtk::TreeModel::iterator> rows_with_no_message;
		std::multimap<uint32_t, std::tuple<can::variable*, can::var_enum*, Gtk::TreeModel::iterator>> rows_with_variable;
	};
}

#endif
