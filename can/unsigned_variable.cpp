#include "unsigned_variable.h"

namespace can
{
    //Constructor
    unsigned_variable::unsigned_variable(uint8_t start, uint8_t length, double factor, double offset, Endianess endian)
        :   _start{start}, _length{length}, _factor{factor}, _offset{offset}, _endian{endian}
    {}

    unsigned_variable::unsigned_variable(const unsigned_variable& v)
        :   _start{v.start()}, _length{v.length()}, _factor{v.factor()}, _offset{v.offset()}, _endian{v.endian()}
    {}

    unsigned_variable::unsigned_variable(unsigned_variable&& v)
        :   _start{std::move(v._start)}, _length{std::move(v._length)}, _factor{std::move(v._factor)}, _offset{std::move(v._offset)}, _endian{std::move(v._endian)}
    {}

    //Member Access
    const uint8_t& unsigned_variable::start() const
    {
        return this->_start;
    }

    const uint8_t& unsigned_variable::length() const
    {
        return this->_length;
    }

    const double& unsigned_variable::factor() const
    {
        return this->_factor;
    }

    const double& unsigned_variable::offset() const
    {
        return this->_offset;
    }

    const Endianess& unsigned_variable::endian() const
    {
        return this->_endian;
    }

    //swap
    void swap(unsigned_variable& v1, unsigned_variable& v2)
    {
        std::swap(v1._start, v2._start);
        std::swap(v1._length, v2._length);
        std::swap(v1._factor, v2._factor);
        std::swap(v1._offset, v2._offset);
        std::swap(v1._endian, v2._endian);
    }
}