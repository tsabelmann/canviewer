#ifndef UTIL_H
#define UTIL_H

#include <inttypes.h>

namespace can
{
    uint8_t mask8_t(uint8_t length);
	uint16_t mask16_t(uint8_t length);
    uint32_t mask32_t(uint8_t length);
	uint64_t mask64_t(uint8_t length);

    uint64_t transformIO(uint8_t const * const data, uint8_t size);
    uint64_t transformRO(uint8_t const * const data, uint8_t size);
}

#endif