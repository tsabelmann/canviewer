#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <mutex>
#include <memory>

#include "TreeModel.h"

namespace gtkmm
{
    class TreeView
    {
        public:
            TreeView();
            ~TreeView() = default;




        private:
            std::mutex m;

            std::unique_ptr<Gtk::TreeView> _treeview;
            std::unuq

    };
}

#endif