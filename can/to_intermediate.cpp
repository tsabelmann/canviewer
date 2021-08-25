#include "to_intermediate.h"

namespace can
{
    to_intermediate::to_intermediate(frame f)
        :   f{f}
    {}

    to_intermediate::storage_type to_intermediate::operator()(bit_variable v)
    {
        uint64_t result = can::transformIO(this->f.data(), this->f.size());
        result >>= v.start();
        result &= 0x01;

        return (result == 0x01 ? true : false);
    }

    to_intermediate::storage_type to_intermediate::operator()(char_variable v)
    {
	    uint64_t _return{0};
        uint64_t _mask = mask64_t(char_variable::length());
                
        auto shift = v.start();

        if(v.endian() == can::Endianess::Motorola)
        {
            _return = can::transformRO(this->f.data(), this->f.size());
            shift = 8 * (this->f.size()) - (v.start()) - (char_variable::length());   
        }
        else
        {
            _return = can::transformIO(this->f.data(), this->f.size());
        }
        
        _return >>= shift;
        _return &= _mask;

        uint8_t *ptr = reinterpret_cast<uint8_t*>(&_return);
        return static_cast<char>(ptr[0]);	
    }

    to_intermediate::storage_type to_intermediate::operator()(float_variable v) 
    {
        uint64_t _return{0};
        uint64_t _mask = mask64_t(float_variable::length());
                
        auto shift = v.start();

        if(v.endian() == can::Endianess::Motorola)
        {
            _return = can::transformRO(this->f.data(), this->f.size());
            shift = 8 * (this->f.size()) - (v.start()) - (float_variable::length());   
        }
        else
        {
            _return = can::transformIO(this->f.data(), this->f.size());
        }
        
        _return >>= shift;
        _return &= _mask;
        
        float result{0.0};

        uint8_t *ptr = reinterpret_cast<uint8_t*>(&_return);
        uint8_t *f_ptr = reinterpret_cast<uint8_t*>(&result);
        std::copy(ptr, ptr + 4, f_ptr);

        return{result * v.factor() + v.offset()};
    }

    to_intermediate::storage_type to_intermediate::operator()(double_variable v)
    {
        uint64_t _return{0};
        uint64_t _mask = mask64_t(double_variable::length());
                
        auto shift = v.start();

        if(v.endian() == can::Endianess::Motorola)
        {
            _return = can::transformRO(this->f.data(), this->f.size());
            shift = 8 * (this->f.size()) - (v.start()) - (double_variable::length());   
        }
        else
        {
            _return = can::transformIO(this->f.data(), this->f.size());
        }
        
        _return >>= shift;
        _return &= _mask;
        
        double result{0.0};

        uint8_t *ptr = reinterpret_cast<uint8_t*>(&_return);
        uint8_t *d_ptr = reinterpret_cast<uint8_t*>(&result);
        std::copy(ptr, ptr + 8, d_ptr);

        return{result * v.factor() + v.offset()};   
    }

    to_intermediate::storage_type to_intermediate::operator()(string_variable v)
    {
        uint64_t _return{0};
        uint64_t _mask = mask64_t(v.length());
                
        auto shift = v.start();

        if(v.endian() == can::Endianess::Motorola)
        {
            _return = can::transformRO(this->f.data(), this->f.size());
            shift = 8 * (this->f.size()) - (v.start()) - (v.length());   
        }
        else
        {
            _return = can::transformIO(this->f.data(), this->f.size());
        }

        _return >>= shift;
        _return &= _mask;

        uint8_t *ptr = reinterpret_cast<uint8_t*>(&_return);
        uint8_t *data = new uint8_t[v.size()];

        for(uint8_t i = 0; i < v.size(); ++i)
        {
            data[i] = ptr[i];
        }

        return{std::string{reinterpret_cast<char*>(data) , v.size()}};
    }

    to_intermediate::storage_type to_intermediate::operator()(signed_variable v)
    {
        uint64_t _return{0};
        uint64_t _mask = mask64_t(v.length());
                
        auto shift = v.start();

        if(v.endian() == can::Endianess::Motorola)
        {
            _return = can::transformRO(this->f.data(), this->f.size());
            shift = 8 * (this->f.size()) - (v.start()) - (v.length());   
        }
        else
        {
            _return = can::transformIO(this->f.data(), this->f.size());
        }
        
        _return >>= shift;
        _return &= _mask;

        int64_t _temp_return = ~_return + 1;

        return{_temp_return * (v.factor()) + (v.offset())};
    }

    to_intermediate::storage_type to_intermediate::operator()(unsigned_variable v)
    {
        uint64_t _return{0};
        uint64_t _mask = mask64_t(v.length());
                
        auto shift = v.start();

        if(v.endian() == can::Endianess::Motorola)
        {
            _return = can::transformRO(this->f.data(), this->f.size());
            shift = 8 * (this->f.size()) - (v.start()) - (v.length());   
        }
        else
        {
            _return = can::transformIO(this->f.data(), this->f.size());
        }
        
        _return >>= shift;
        _return &= _mask;

        return{_return * v.factor() + v.offset()};
    }

    to_intermediate::storage_type to_intermediate::operator()(raw_variable v)
    {
        uint64_t _return = can::transformIO(this->f.data(), this->f.size());
        uint64_t _mask = mask64_t(v.length());

        auto shift = v.start();

        _return >>= shift;
        _return &= _mask;

        return{_return};
    }
}
