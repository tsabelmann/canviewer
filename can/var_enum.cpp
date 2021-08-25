#include "var_enum.h"

namespace can
{
    //constructor
    var_enum::var_enum(std::string name)
        :   _name{name}, _values{}
    {}

    var_enum::var_enum(const var_enum& e)
        :   _name{e.name()}, _values{e._values}
    {}

    var_enum::var_enum(var_enum&& e)
        :   _name{std::move(e._name)}, _values{std::move(e._values)}
    {}

    //insert
    var_enum& var_enum::insert(bool b, std::string content)
    {
        this->_values.insert(std::make_pair(b, content));
        return *this;
    }

    var_enum& var_enum::insert(char c, std::string content)
    {
        this->_values.insert(std::make_pair(c, content));
        return *this;
    }

    var_enum& var_enum::insert(double d, std::string content)
    {
        this->_values.insert(std::make_pair(d, content));
        return *this;
    }

    var_enum& var_enum::insert(float f, std::string content)
    {
        this->_values.insert(std::make_pair(f, content));
        return *this;
    }

    var_enum& var_enum::insert(std::string s, std::string content)
    {
        this->_values.insert(std::make_pair(s, content));
        return *this;
    }

    var_enum& var_enum::insert(uint64_t i, std::string content)
    {
        this->_values.insert(std::make_pair(i, content));
        return *this;
    }

    var_enum& var_enum::insert(var_enum::first_type v, std::string content)
    {
        this->_values.insert(std::make_pair(v, content));
        return *this;  
    }

    //access (lookup)
    var_enum::opt_string var_enum::operator[](bool b) const
    {
        auto found = this->_values.find(b);
        if(found != this->_values.end())
        {
            return{found->second};
        }

        return{};
    }

    var_enum::opt_string var_enum::operator[](char c) const
    {
        auto found = this->_values.find(c);
        if(found != this->_values.end())
        {
            return{found->second};
        }

        return{};
    }

    var_enum::opt_string var_enum::operator[](double d) const
    {
        auto found = this->_values.find(d);
        if(found != this->_values.end())
        {
            return{found->second};
        }

        return{};
    }

    var_enum::opt_string var_enum::operator[](float f) const
    {
        auto found = this->_values.find(f);
        if(found != this->_values.end())
        {
            return{found->second};
        }

        return{};
    }

    var_enum::opt_string var_enum::operator[](std::string s) const
    {
        auto found = this->_values.find(s);
        if(found != this->_values.end())
        {
            return{found->second};
        }

        return{};
    }

    var_enum::opt_string var_enum::operator[](uint64_t i) const
    {
        auto found = this->_values.find(i);
        if(found != this->_values.end())
        {
            return{found->second};
        }

        return{};
    }

    var_enum::opt_string var_enum::operator[](var_enum::first_type v) const
    {
        auto found = this->_values.find(v);
        if(found != this->_values.end())
        {
            return{found->second};
        }

        return{};
    }

    //member access
    const std::string& var_enum::name() const
    {
        return this->_name;
    }

    const var_enum::map_type& var_enum::values() const
    {
        return this->_values;
    }

    //operator=
    void swap(var_enum& e1, var_enum& e2)
    {
        std::swap(e1._name, e2._name);
        std::swap(e1._values, e2._values);
    }
}