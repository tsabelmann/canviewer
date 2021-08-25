#include "float_variable.h"

namespace can
{
    const uint8_t float_variable::_length{32};

    //Constructor
    float_variable::float_variable(uint8_t start, float factor, float offset, Endianess endian)
        :   _start{start}, _factor{factor}, _offset{offset}, _endian{endian}
    {}

    float_variable::float_variable(const float_variable& v)
        :   _start{v.start()}, _factor{v.factor()}, _offset{v.offset()}, _endian{v.endian()}
    {}

    float_variable::float_variable(float_variable&& v)
        :   _start{std::move(v._start)}, _factor{std::move(v._factor)}, _offset{std::move(v._offset)}, _endian{std::move(v._endian)}
    {}

    //Member Access
    const uint8_t& float_variable::start() const
    {
        return this->_start;
    }
    
    const float& float_variable::factor() const
    {
        return this->_factor;
    }

    const float& float_variable::offset() const
    {
        return this->_offset;
    }

    const uint8_t& float_variable::length()
    {
        return float_variable::_length;
    }

    const Endianess& float_variable::endian() const
    {
        return this->_endian;
    }

    //swap
    void swap(float_variable& v1, float_variable& v2)
    {
        std::swap(v1._start, v2._start);
        std::swap(v1._factor, v2._factor);
        std::swap(v1._offset, v2._offset);
        std::swap(v1._endian, v2._endian);
    }
}




