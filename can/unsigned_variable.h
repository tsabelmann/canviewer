#ifndef CAN_UNSIGNED_VARIABLE_H
#define CAN_UNSIGNED_VARIABLE_H

#include "endian.h"
#include <utility>

namespace can
{
    class unsigned_variable
    {
        public:
            unsigned_variable(uint8_t start, uint8_t length, double factor = 1.0, double offset = 0.0, Endianess endian = Endianess::Intel);
            unsigned_variable(const unsigned_variable& v);
            unsigned_variable(unsigned_variable&& v);
            ~unsigned_variable() = default;

            //operator=
            template<typename T>
            unsigned_variable& operator=(T&& v)
            {
                unsigned_variable temp{std::forward<T>(v)};
                swap(temp, *this);
                return *this;
            }
            friend void swap(unsigned_variable& v1, unsigned_variable& v2);
            
            //Member access
            const uint8_t& start() const;
            const uint8_t& length() const;
            const double& factor() const;
            const double& offset() const;
            const Endianess& endian() const;

        private:
            uint8_t _start;
            uint8_t _length;
            double _factor;
            double _offset;
            Endianess _endian;
    };

    void swap(unsigned_variable& v1, unsigned_variable& v2);
}

#endif