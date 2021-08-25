#include "variable.h"

namespace can
{
    //Constructor
    variable::variable(bit_variable v, std::string name, std::string phys_unit, std::string enum_name)
        :   _var{v}, _type{variable::variable_type::Bit}, _name{name}, _phys_unit{phys_unit}, _enum_name{enum_name}
    {}

    variable::variable(char_variable v, std::string name, std::string phys_unit, std::string enum_name)
        :   _var{v}, _type{variable::variable_type::Char}, _name{name}, _phys_unit{phys_unit}, _enum_name{enum_name}
    {}

    variable::variable(double_variable v, std::string name, std::string phys_unit, std::string enum_name)
        :   _var{v}, _type{variable::variable_type::Double}, _name{name}, _phys_unit{phys_unit}, _enum_name{enum_name}
    {}
    
    variable::variable(float_variable v, std::string name, std::string phys_unit, std::string enum_name)
        :   _var{v}, _type{variable::variable_type::Float}, _name{name}, _phys_unit{phys_unit}, _enum_name{enum_name}
    {}

    variable::variable(unsigned_variable v, std::string name, std::string phys_unit, std::string enum_name)
        :   _var{v}, _type{variable::variable_type::Unsigned}, _name{name}, _phys_unit{phys_unit}, _enum_name{enum_name}
    {}

    variable::variable(signed_variable v, std::string name, std::string phys_unit, std::string enum_name)
        :   _var{v}, _type{variable::variable_type::Signed}, _name{name}, _phys_unit{phys_unit}, _enum_name{enum_name}
    {}

    variable::variable(string_variable v, std::string name, std::string phys_unit, std::string enum_name)
        :   _var{v}, _type{variable::variable_type::String}, _name{name}, _phys_unit{phys_unit}, _enum_name{enum_name}
    {}

    variable::variable(raw_variable v, std::string name, std::string phys_unit, std::string enum_name)
        :   _var{v}, _type{variable::variable_type::Raw}, _name{name}, _phys_unit{phys_unit}, _enum_name{enum_name}
    {}

    variable::variable(const variable& v)
        :   _name{v.name()}, _phys_unit{v.phys_unit()}, _enum_name{v.enum_name()}, _var{v.var()}
    {}

    variable::variable(variable&& v)
        :   _name{std::move(v._name)}, _phys_unit{std::move(v._phys_unit)}, _enum_name{std::move(v._enum_name)}, _var{std::move(v._var)}
    {}

    variable::operator bit_variable()
    {
        return std::get<bit_variable>(this->_var);
    }

    variable::operator char_variable()
    {
        return std::get<char_variable>(this->_var);
    }

    variable::operator double_variable()
    {
        return std::get<double_variable>(this->_var);
    }

    variable::operator float_variable()
    {
        return std::get<float_variable>(this->_var);
    }

    variable::operator unsigned_variable()
    {
        return std::get<unsigned_variable>(this->_var);
    }

    variable::operator signed_variable()
    {
        return std::get<signed_variable>(this->_var);
    }

    variable::operator string_variable()
    {
        return std::get<string_variable>(this->_var);
    }

    variable::operator raw_variable()
    {
        return std::get<raw_variable>(this->_var);
    }

    //Member Access
    const variable::storage_type& variable::var() const
    {
        return this->_var;
    }

    const variable::variable_type& variable::type() const
    {
        return this->_type;
    }

    const std::string& variable::name() const
    {
        return this->_name;
    }

    const std::string& variable::phys_unit() const
    {
        return this->_phys_unit;
    }

    const std::string& variable::enum_name() const
    {
        return this->_enum_name;
    }

    //swap
    void swap(variable& v1, variable& v2)
    {
        std::swap(v1._name, v2._name);
        std::swap(v1._phys_unit, v2._phys_unit);
        std::swap(v1._enum_name, v2._enum_name);
        std::swap(v1._var, v2._var);
    }
}