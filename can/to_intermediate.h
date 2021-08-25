#ifndef CAN_TO_INTERMEDIATE_H
#define CAN_TO_INTERMEDIATE_H

#include <variant>

#include "util.h"
#include "frame.h"

#include "bit_variable.h"
#include "char_variable.h"
#include "float_variable.h"
#include "double_variable.h"
#include "string_variable.h"
#include "signed_variable.h"
#include "unsigned_variable.h"
#include "raw_variable.h"

namespace can
{
    class to_intermediate
    {
        public:
            using storage_type = std::variant<bool, char, double, float, std::string, uint64_t>;
            to_intermediate(frame f);
            ~to_intermediate() = default;

            //operator()
            storage_type operator()(bit_variable v);
            storage_type operator()(char_variable v);
            storage_type operator()(double_variable v);
            storage_type operator()(float_variable v);
            storage_type operator()(unsigned_variable v);
            storage_type operator()(signed_variable v);
            storage_type operator()(string_variable v);
            storage_type operator()(raw_variable v);

        private:
            frame f;
    };
}

#endif