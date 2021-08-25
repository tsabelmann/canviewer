#ifndef CAN_STRING_VARIABLE_H
#define CAN_STRING_VARIABLE_H

#include "endian.h"
#include <utility>

namespace can
{
    class string_variable
    {
        public:
            string_variable(uint8_t start, uint8_t size, Endianess endian = Endianess::Intel);
            string_variable(const string_variable& v);
            string_variable(string_variable&& v);
            ~string_variable() = default;

            //operator=
            template<typename T>
            string_variable& operator=(T&& v)
            {
                string_variable temp{std::forward<T>(v)};
                swap(temp, *this);
                return *this;
            }
            friend void swap(string_variable& v1, string_variable& v2);

            //Member access
            const uint8_t& start() const;
            const uint8_t& size() const;
            uint8_t length() const;
            const Endianess& endian() const;

        private:
            uint8_t _start;
            uint8_t _size;
            Endianess _endian;
    };

    void swap(string_variable& v1, string_variable& v2);
}

#endif