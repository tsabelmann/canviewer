#ifndef CAN_TO_STRING_H
#define CAN_TO_STRING_H

#include "var_enum.h"
#include "variable.h"

#include <iomanip>
#include <sstream>

namespace can
{
    class to_string
    {
        public:
            to_string();
            to_string(var_enum e);
            ~to_string() = default;

            std::string operator()(bool b);
            std::string operator()(char c);
            std::string operator()(double d);
            std::string operator()(float f);
            std::string operator()(std::string s);
            std::string operator()(uint64_t b);

        private:
            std::optional<var_enum> opt_enum;
    };
}

#endif