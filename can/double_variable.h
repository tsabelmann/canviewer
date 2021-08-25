 #ifndef CAN_DOUBLE_VARIABLE_H
#define CAN_DOUBLE_VARIABLE_H

#include "endian.h"
#include <utility>

namespace can
{
    class double_variable
    {
        public:
            double_variable( uint8_t start, double factor = 1.0, double offset = 0.0, Endianess endian = Endianess::Intel);
            double_variable(const double_variable& v);
            double_variable(double_variable&& v);
            ~double_variable() = default;

            template<typename T>
            double_variable operator=(T&& v)
            {
                double_variable temp{std::forward<double_variable>(v)};
                swap(temp, *this);
                return *this;
            }
            friend void swap(double_variable& v1, double_variable& v2);

            //Member access
            const uint8_t& start() const;
            const double& factor() const;
            const double& offset() const;
            const Endianess& endian() const;

            static const uint8_t& length();

        private:
            double _factor;
            double _offset;
            uint8_t _start;
            Endianess _endian;

            static const uint8_t _length;
    };

    void swap(double_variable& v1, double_variable& v2);
}

#endif