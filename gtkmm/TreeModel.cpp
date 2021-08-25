#include "TreeModel.h"

namespace gtkmm
{
    TreeModel::TreeModel()
    {
        this->add(this->id);
        this->add(this->m_name);
        this->add(this->v_name);

        this->add(this->data);
        this->add(this->phys_unit);

        this->add(this->id_type);
        this->add(this->interface);

        this->add(this->count);
        this->add(this->cycle_time);
    }
}
