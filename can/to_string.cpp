#include "to_string.h"

namespace can
{
    to_string::to_string()
        :   opt_enum{}
    {}

    to_string::to_string(var_enum e)
        :   opt_enum{e}
    {}

    std::string to_string::operator()(bool b)
    {
        if(this->opt_enum)
        {
            auto value = this->opt_enum.value()[b];
            if(value)
                return value.value();
            else
            {
                if(b)
                    return std::string{"true"};
                else
                    return std::string{"false"};
            }
        }
        else
        {
            if(b)
                return std::string{"true"};
            else
                return std::string{"false"};
        }
    }

    std::string to_string::operator()(char c)
    {
        if(this->opt_enum)
        {
            auto value = this->opt_enum.value()[c];
            if(value)
                return value.value();
            else
            {
                return{c};
            }
        }
        else
        {
            return{c};
        }
    }

    std::string to_string::operator()(double d)
    {
        if(this->opt_enum)
        {
            auto value = this->opt_enum.value()[d];
            if(value)
                return value.value();
            else
            {
                std::stringstream ss;
                ss << std::fixed << std::setprecision(2) << d;
                return ss.str();
            }
        }
        else
        {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << d;
            return ss.str();
        }
    }

    std::string to_string::operator()(float f)
    {
        if(this->opt_enum)
        {
            auto value = this->opt_enum.value()[f];
            if(value)
                return value.value();
            else
            {
                std::stringstream ss;
                ss << std::fixed << std::setprecision(2) << f;
                return ss.str();
            }
        }
        else
        {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << f;
            return ss.str();
        }
    }

    std::string to_string::operator()(std::string s)
    {
        if(this->opt_enum)
        {
            auto value = this->opt_enum.value()[s];
            if(value)
                return value.value();
            else
            {
                return s;
            }
        }
        else
        {
            return s;
        }
    }

    std::string to_string::operator()(uint64_t i)
    {        
        if(this->opt_enum)
        {
            auto value = this->opt_enum.value()[i];
            if(value)
                return value.value();
            else
            {
                return std::to_string(i);
            }
        }
        else
        {
            return std::to_string(i);
        }
    }
}