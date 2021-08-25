#include "string_variable.h"

namespace can
{
    //Constructor
    string_variable::string_variable(uint8_t start, uint8_t size, Endianess endian)
        :    _start{start}, _size{size}, _endian{endian}
    {}

    string_variable::string_variable(const string_variable& v)
        :   _start{v.start()}, _size{v.size()}, _endian{v.endian()}
    {}

    string_variable::string_variable(string_variable&& v)
        :   _start{std::move(v._start)}, _size{std::move(v._size)}, _endian{std::move(v._endian)}
    {}

    //Member Access
    const uint8_t& string_variable::start() const
    {
        return this->_start;
    }

    const uint8_t& string_variable::size() const
    {
        return this->_size;
    }

    uint8_t string_variable::length() const
    {
        return (8 * this->_size);
    }

    const Endianess& string_variable::endian() const
    {
        return this->_endian;
    }

    //swap
    void swap(string_variable& v1, string_variable& v2)
    {
        std::swap(v1._start, v2._start);
        std::swap(v1._size, v2._size);
        std::swap(v1._endian, v2._endian);
    }
}




