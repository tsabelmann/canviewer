#ifndef ENDIAN_H
#define ENDIAN_H

#include <inttypes.h>

namespace can
{
    enum class Endianess{Intel, Motorola};

    constexpr bool is_little_endian()
    {
        uint16_t value = 0x0001;
        uint8_t *ptr = reinterpret_cast<uint8_t*>(&value);
        if(ptr[0] == 0x01)
            return true;
        else
            return false;
    }

    constexpr bool is_big_endian()
    {
        uint16_t value = 0x0001;
        uint8_t *ptr = reinterpret_cast<uint8_t*>(&value);
        if(ptr[0] == 0x01)
            return false;
        else
            return true;
    }
}

#endif