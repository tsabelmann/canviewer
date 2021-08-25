#include "ListModel.h"

namespace gtkmm
{
    ListModel::ListModel()
    {
        this->add(this->interface_name);
        this->add(this->active);
    }
}
