#ifndef CAN_SIGNED_VARIABLE_H
#define CAN_SIGNED_VARIABLE_H

#include "endian.h"
#include <utility>

namespace can
{
    class signed_variable
    {
        public:
            signed_variable(uint8_t start, uint8_t length, double factor = 1.0, double offset = 0.0, Endianess endian = Endianess::Intel);
            signed_variable(const signed_variable& v);
            signed_variable(signed_variable&& v);
            ~signed_variable() = default;

            //operator=
            template<typename T>
            signed_variable& operator=(T&& v)
            {
                signed_variable temp{std::forward<T>(v)};
                swap(temp, *this);
                return *this;
            }
            friend void swap(signed_variable& v1, signed_variable& v2);

            //Member access
            const uint8_t& start() const;
            const uint8_t& length() const;
            const double& factor() const;
            const double& offset() const;
            const Endianess& endian() const;

        private:
            double _factor;
            double _offset;
            uint8_t _start;
            uint8_t _length;
            Endianess _endian;
    };

    void swap(signed_variable& v1, signed_variable& v2);
}

#endif