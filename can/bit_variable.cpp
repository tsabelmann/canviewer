#include "bit_variable.h"

namespace can
{
    //Constructor
    bit_variable::bit_variable(uint8_t start)
        :    _start{start}
    {}

    bit_variable::bit_variable(const bit_variable& v)
        :   _start{v.start()}
    {}

    bit_variable::bit_variable(bit_variable&& v)
        :   _start{std::move(v._start)}
    {}

    //Member Access
    const uint8_t& bit_variable::start() const
    {
        return this->_start;
    }

    //swap
    void swap(bit_variable& v1, bit_variable& v2)
    {
        std::swap(v1._start, v2._start);
    }
}




