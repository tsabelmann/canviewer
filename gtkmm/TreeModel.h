#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <gtkmm/treemodelcolumn.h>

namespace gtkmm
{
	class TreeModel : public Gtk::TreeModelColumnRecord
	{
	public:
		TreeModel();
		virtual ~TreeModel() = default;

		Gtk::TreeModelColumn<std::string> id;
		Gtk::TreeModelColumn<std::string> m_name;
		Gtk::TreeModelColumn<std::string> v_name;

		Gtk::TreeModelColumn<std::string> data;
		Gtk::TreeModelColumn<std::string> phys_unit;

		Gtk::TreeModelColumn<std::string> id_type;
		Gtk::TreeModelColumn<std::string> interface;
		Gtk::TreeModelColumn<std::string> count;
		Gtk::TreeModelColumn<std::string> cycle_time;
	};
}

#endif
