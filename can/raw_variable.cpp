#include "raw_variable.h"

namespace can
{
    //Constructor
    raw_variable::raw_variable(uint8_t start, uint8_t length)
        :   _start{start}, _length{length}
    {}

    raw_variable::raw_variable(const raw_variable& v)
        :   _start{v.start()}, _length{v.length()}
    {}

    raw_variable::raw_variable(raw_variable&& v)
        :   _start{std::move(v._start)}, _length{std::move(v._length)}
    {}

    //Member Access
    const uint8_t& raw_variable::start() const
    {
        return this->_start;
    }

    const uint8_t& raw_variable::length() const
    {
        return this->_length;
    }

    //swap
    void swap(raw_variable& v1, raw_variable& v2)
    {
        std::swap(v1._start, v2._start);
        std::swap(v1._length, v2._length);
    }
}




