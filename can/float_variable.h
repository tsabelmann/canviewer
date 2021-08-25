#ifndef CAN_FLOAT_VARIABLE_H
#define CAN_FLOAT_VARIABLE_H

#include "endian.h"
#include <utility>

namespace can
{
    class float_variable
    {
        public:
            float_variable(uint8_t start, float factor = 1.0, float offset = 0.0, Endianess endian = Endianess::Intel);    
            float_variable(const float_variable& v);
            float_variable(float_variable&& v);        
            ~float_variable() = default;

            //operator=
            template<typename T>
            float_variable& operator=(T&& v)
            {
                float_variable temp{std::forward<T>(v)};
                swap(temp, *this);
                return *this;
            }
            friend void swap(float_variable& v1, float_variable& v2);

            //Member access
            const uint8_t& start() const;
            const float& factor() const;
            const float& offset() const;
            const Endianess& endian() const;

            static const uint8_t& length();

        private:
            float _factor;
            float _offset;
            uint8_t _start;
            Endianess _endian;

            static const uint8_t _length;
    };

    void swap(float_variable& v1, float_variable& v2);
}

#endif