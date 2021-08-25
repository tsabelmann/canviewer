#include "util.h"

namespace can
{
    uint8_t mask8_t(uint8_t length)
    {
        uint8_t result{0};
        if(length != 0)
        {
            for(uint8_t i = 0; i < length - 1; ++i)
            {
                result += 1;
                result <<= 1;
            }
            result += 1;
        }
        return result;
    }

	uint16_t mask16_t(uint8_t length)
    {
        uint16_t result{0};
        if(length != 0)
        {
            for(uint8_t i = 0; i < length - 1; ++i)
            {
                result += 1;
                result <<= 1;
            }
            result += 1;
        }
        return result;
    }

    uint32_t mask32_t(uint8_t length)
    {
        uint32_t result{0};
        if(length != 0)
        {
            for(uint8_t i = 0; i < length - 1; ++i)
            {
                result += 1;
                result <<= 1;
            }
            result += 1;
        }
        return result;
    }

	uint64_t mask64_t(uint8_t length)
    {
        uint64_t result{0};
        if(length != 0)
        {
            for(uint8_t i = 0; i < length - 1; ++i)
            {
                result += 1;
                result <<= 1;
            }
            result += 1;
        }
        return result;
    }

    uint64_t transformIO(uint8_t const * const data, uint8_t size)
    {
        uint64_t result{0};
        uint8_t *ptr = reinterpret_cast<uint8_t*>(&result);

        for(uint8_t i = 0; i < size; ++i)
        {
            ptr[i] = data[i];
        }
        
        return result;
    }

    uint64_t transformRO(uint8_t const * const data, uint8_t size)
    {
        uint64_t result{0};
        uint8_t *ptr = reinterpret_cast<uint8_t*>(&result);

        for(uint8_t i = 0; i < size; ++i)
        {
            ptr[size - 1 - i] = data[i];
        }
        
        return result;
    }
}