#ifndef CAN_CHAR_VARIABLE_H
#define CAN_CHAR_VARIABLE_H

#include "endian.h"
#include <utility>

namespace can
{
    class char_variable
    {
        public:
            char_variable(uint8_t start, Endianess endian = Endianess::Intel);
            char_variable(const char_variable& v);
            char_variable(char_variable&& v);
            ~char_variable() = default;

            //operator=
            template<typename T>
            char_variable& operator=(T&& v)
            {
                char_variable temp{std::forward<T>(v)};
                swap(temp, *this);
                return *this;
            }
            friend void swap(char_variable& v1, char_variable& v2);

            //Member access
            const uint8_t& start() const;
            const Endianess& endian() const;

            static const uint8_t& length();

        private:
            uint8_t _start;
            Endianess _endian;

            static const uint8_t _length;
    };

    void swap(char_variable& v1, char_variable& v2);
}

#endif