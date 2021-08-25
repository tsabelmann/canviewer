#ifndef CAN_RAW_VARIABLE_H
#define CAN_RAW_VARIABLE_H

#include "endian.h"
#include <utility>

namespace can
{
    class raw_variable
    {
        public:
            raw_variable(uint8_t start, uint8_t length);
            raw_variable(const raw_variable& v);
            raw_variable(raw_variable&& v);
            ~raw_variable() = default;

            template<typename T>
            raw_variable& operator=(T&& v)
            {
                raw_variable temp{std::forward<T>(v)};
                swap(temp, *this);
                return *this;
            }
            friend void swap(raw_variable& v1, raw_variable& v2);

            //Member access
            const uint8_t& start() const;
            const uint8_t& length() const;

        private:
            uint8_t _start;
            uint8_t _length;
    };

    void swap(raw_variable& v1, raw_variable& v2);
}

#endif