#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <variant>
#include <iostream>

#include "bit_variable.h"
#include "char_variable.h"
#include "double_variable.h"
#include "float_variable.h"
#include "unsigned_variable.h"
#include "signed_variable.h"
#include "string_variable.h"
#include "raw_variable.h"

namespace can
{
    class variable
    {  
        public:
            enum class variable_type{Bit, Char, Float, Double, Signed, Unsigned, String, Raw};
            using storage_type = std::variant<bit_variable, char_variable, double_variable, float_variable, unsigned_variable, signed_variable, string_variable, raw_variable>;

            //Constructor, Destructor
            variable(bit_variable v, std::string name, std::string phys_unit, std::string enum_name);
            variable(char_variable v, std::string name, std::string phys_unit, std::string enum_name);
            variable(double_variable v, std::string name, std::string phys_unit, std::string enum_name);
            variable(float_variable v, std::string name, std::string phys_unit, std::string enum_name);
            variable(unsigned_variable v, std::string name, std::string phys_unit, std::string enum_name);
            variable(signed_variable v, std::string name, std::string phys_unit, std::string enum_name);
            variable(string_variable v, std::string name, std::string phys_unit, std::string enum_name);
            variable(raw_variable v, std::string name, std::string phys_unit, std::string enum_name);
            
            variable(const variable& v);
            variable(variable&& v);
            ~variable() = default;

            //operator=
            template<typename T>
            variable& operator=(T&& v)
            {
                variable temp{std::forward<T>(v)};
                swap(temp, *this);
                return *this;
            }
            friend void swap(variable& v1, variable& v2);
            
            //operator overloading
            operator bit_variable();
            operator char_variable();
            operator double_variable();
            operator float_variable();
            operator unsigned_variable();
            operator signed_variable();
            operator string_variable();
            operator raw_variable();

            //Member Access
            const storage_type& var() const;
            const variable_type& type() const;
            const std::string& name() const;
            const std::string& phys_unit() const;
            const std::string& enum_name() const;

        private:
            storage_type _var;
            variable_type _type;
            std::string _name;
            std::string _phys_unit;
            std::string _enum_name;
    };

    void swap(variable& v1, variable& v2);
}

#endif