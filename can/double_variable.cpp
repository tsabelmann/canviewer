#include "double_variable.h"

namespace can
{
    const uint8_t double_variable::_length{64};

    //Constructor
    double_variable::double_variable(uint8_t start, double factor, double offset,  Endianess endian)
        :   _start{start}, _factor{factor}, _offset{offset}, _endian{endian}
    {}

    double_variable::double_variable(const double_variable& v)
        :   _factor{v.factor()}, _offset{v.offset()}, _start{v.start()}, _endian{v.endian()}
    {}

    double_variable::double_variable(double_variable&& v)
        :    _start{std::move(v._start)}, _factor{std::move(v._factor)}, _offset{std::move(v._offset)}, _endian{std::move(v._endian)}
    {}

    //Member Access
    const uint8_t& double_variable::start() const
    {
        return this->_start;
    }
    
    const double& double_variable::factor() const
    {
        return this->_factor;
    }

    const double& double_variable::offset() const
    {
        return this->_offset;
    }

    const uint8_t& double_variable::length()
    {
        return double_variable::_length;
    }

    const Endianess& double_variable::endian() const
    {
        return this->_endian;
    }

    //swap
    void swap(double_variable& v1, double_variable& v2)
    {
        std::swap(v1._start, v2._start);
        std::swap(v1._factor, v2._factor);
        std::swap(v1._offset, v2._offset);
        std::swap(v1._endian, v2._endian);
    }
}




