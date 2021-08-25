#include "signed_variable.h"

namespace can
{
    //Constructor
    signed_variable::signed_variable(uint8_t start, uint8_t length, double factor, double offset, Endianess endian)
        :   _start{start}, _length{length}, _factor{factor}, _offset{offset}, _endian{endian}
    {}

    signed_variable::signed_variable(const signed_variable& v)
        :   _start{v.start()}, _length{v.length()}, _factor{v.factor()}, _offset{v.offset()}, _endian{v.endian()}
    {}

    signed_variable::signed_variable(signed_variable&& v)
        :   _start{std::move(v._start)}, _length{std::move(v._length)}, _factor{std::move(v._factor)}, _offset{std::move(v._offset)}, _endian{std::move(v._endian)}
    {}

    //Member Access
    const uint8_t& signed_variable::start() const
    {
        return this->_start;
    }

    const uint8_t& signed_variable::length() const
    {
        return this->_length;
    }
    
    const double& signed_variable::factor() const
    {
        return this->_factor;
    }

    const double& signed_variable::offset() const
    {
        return this->_offset;
    }

    const Endianess& signed_variable::endian() const
    {
        return this->_endian;
    }

    //swap
    void swap(signed_variable& v1, signed_variable& v2)
    {
        std::swap(v1._start, v2._start);
        std::swap(v1._length, v2._length);
        std::swap(v1._factor, v2._factor);
        std::swap(v1._offset, v2._offset);
        std::swap(v1._endian, v2._endian);
    }
}




