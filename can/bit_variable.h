#ifndef CAN_BIT_VARIABLE_H
#define CAN_BIT_VARIABLE_H

#include "endian.h"
#include <utility>

namespace can
{
    class bit_variable
    {
        public:
            bit_variable(uint8_t start);
            bit_variable(const bit_variable& v);
            bit_variable(bit_variable&& v);
            ~bit_variable() = default;

            //operator=
            template<typename T>
            bit_variable& operator=(T&& v)
            {
                bit_variable temp{std::forward<T>(v)};
                swap(temp, *this);
                return *this;
            }
            friend void swap(bit_variable& v1, bit_variable& v2);

            //Member access
            const uint8_t& start() const;

        private:
            uint8_t _start;
    };

    void swap(bit_variable& v1, bit_variable& v2);
}

#endif