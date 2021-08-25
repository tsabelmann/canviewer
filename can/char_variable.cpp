#include "char_variable.h"

namespace can
{
    const uint8_t char_variable::_length{8};

    //Constructor
    char_variable::char_variable(uint8_t start, Endianess endian)
        :  _start{start}, _endian{endian}
    {}

    char_variable::char_variable(const char_variable& v)
        :   _start{v.start()}, _endian{v.endian()}
    {}

    char_variable::char_variable(char_variable&& v)
        :   _start{std::move(v._start)}, _endian{std::move(v._endian)}
    {}

    //Member Access
    const uint8_t& char_variable::start() const
    {
        return this->_start;
    }

    const uint8_t& char_variable::length()
    {
        return char_variable::_length;
    }

    const Endianess& char_variable::endian() const
    {
        return this->_endian;
    }

    //swap
    void swap(char_variable& v1, char_variable& v2)
    {
        std::swap(v1._start, v2._start);
        std::swap(v1._endian, v2._endian);
    }
}




