#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <gtkmm/treemodelcolumn.h>

namespace gtkmm
{
	class ListModel : public Gtk::TreeModelColumnRecord
	{
	public:
		ListModel();
		virtual ~ListModel() = default;

		Gtk::TreeModelColumn<std::string> interface_name;
		Gtk::TreeModelColumn<bool> active;
	};
}

#endif
