#ifndef FRAME_H
#define FRAME_H

#include <inttypes.h>
#include <optional>

namespace can
{
    class frame
    {
        public:
            // using hr_clock = std::chrono::high_resolution_clock;
            // using duration = std::chrono::milliseconds;
            // using time_point = std::chrono::time_point<hr_clock, duration>;

            enum class Format{Standard, Extended};

            //Constructor
            frame(uint32_t can_id, uint8_t const * const data, uint8_t size, Format format = Format::Standard);
            frame(uint32_t can_id, uint8_t data, Format format = Format::Standard);
            frame(uint32_t can_id, uint16_t data, Format format = Format::Standard);
            frame(uint32_t can_id, uint32_t data, Format format = Format::Standard);
            frame(uint32_t can_id, uint64_t data, Format format = Format::Standard);

            frame(const frame&);
            frame(frame&& frame);
            
            //Destructor
            ~frame();

            //Assignment
            frame& operator=(const frame&);
            frame& operator=(frame&& frame);
            std::optional<uint8_t> operator[](uint8_t position) const;

            //Member Access
            const uint32_t& can_id() const;
            uint8_t const * const data() const;
            const uint8_t& size() const;
            const Format& format() const;

            //Friend Swap Function
            friend void swap(frame& frame1, frame& frame2);

        private:      
            uint32_t _can_id;
            uint8_t * _data;
            uint8_t _size;
            Format _format;
            // time_point _timestamp;
    };

    void swap(frame& frame1, frame& frame2);
}

#endif