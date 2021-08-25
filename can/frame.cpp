#include "frame.h"
#include <iostream>

namespace can
{
    //Constructor
    frame::frame(uint32_t can_id, uint8_t const * const data, uint8_t size, Format format)
        :   _can_id{can_id}, _data{new uint8_t[size]}, _size{size}, _format{format}
    {
        for(uint8_t i = 0; i < size; ++i)
        {
            this->_data[i] = data[i];
        }
    }

    frame::frame(uint32_t can_id, uint8_t data, Format format)
        :   _can_id{can_id}, _data{new uint8_t}, _format{format}
    {
        this->_data[0] = data;
    }

    frame::frame(uint32_t can_id, uint16_t data, Format format)
        :   _can_id{can_id}, _data{new uint8_t[2]}, _size{2}, _format{format}
    {
        uint8_t *ptr = reinterpret_cast<uint8_t*>(&data);

        for(uint8_t i = 0; i < 2; ++i)
        {
            this->_data[i] = ptr[i];
        }
    }
    
    frame::frame(uint32_t can_id, uint32_t data, Format format)
        :   _can_id{can_id}, _data{new uint8_t[4]}, _size{4}, _format{format}
    {
        uint8_t *ptr = reinterpret_cast<uint8_t*>(&data);
        for(uint8_t i = 0; i < 4; ++i)
        {
            this->_data[i] = ptr[i];
        }
    }

    frame::frame(uint32_t can_id, uint64_t data, Format format)
        :   _can_id{can_id}, _data{new uint8_t[8]}, _size{8}, _format{format}
    {
        uint8_t *ptr = reinterpret_cast<uint8_t*>(&data);
        for(uint8_t i = 0; i < 8; ++i)
        {
            this->_data[i] = ptr[i];
        }
    }

    frame::frame(const frame& frame)
        :   _can_id{frame.can_id()}, _data{new uint8_t[frame.size()]}, _size{frame.size()}, _format{frame.format()}
    {
        for(uint8_t i = 0; i < _size; ++i)
        {
            this->_data[i] = frame.data()[i];
        }
    }

    frame::frame(frame&& frame)
        :   _can_id{std::move(frame._can_id)}, _data{std::move(frame._data)}, _size{std::move(frame._size)}, _format{std::move(frame._format)}
    {
        frame._data = nullptr;
    }

    frame::~frame()
    {
        if(this->_data)
        {
            delete[] this->_data;
            this->_data = nullptr;
        }

    }

    //Assignment
    frame& frame::operator=(const frame& fr)
    {
        frame tmp{fr};
        swap(*this, tmp);
        return *this;
    }

    frame& frame::operator=(frame&& fr)
    {
        frame tmp{std::move(fr)};
        swap(*this, tmp);
        return *this;
    }

    std::optional<uint8_t> frame::operator[](uint8_t position) const
    {
        if(position < this->_size)
        {
            return{this->_data[position]};
        }
        
        return{};
    }

    //Member Access
    const uint32_t& frame::can_id() const
    {
        return this->_can_id;
    }

    uint8_t const * const frame::data() const
    {
        return this->_data;
    }

    const uint8_t& frame::size() const
    {
        return this->_size;
    }

    const frame::Format& frame::format() const
    {
        return this->_format;
    }

    void swap(frame& frame1, frame& frame2)
    {
        std::swap(frame1._can_id, frame2._can_id);
        std::swap(frame1._data, frame2._data);
        std::swap(frame1._size, frame2._size);
        std::swap(frame1._format, frame2._format);
        // std::swap(frame1._timestamp, frame2._timestamp);
    }
}