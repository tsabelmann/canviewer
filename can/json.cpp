#include "json.h"

namespace can
{
    json::json(std::string path)
        :   _messages{}, _enums{}
    {
        boost::property_tree::ptree root;
        boost::property_tree::read_json(path, root);

        auto messages = root.get_child("messages");
        for(auto message_iter : messages)
        {
            auto message            = message_iter.second;
            auto message_id_str     = message.get<std::string>("id", "");
            auto message_name       = message.get<std::string>("name", "");
            auto message_type_str   = message.get<std::string>("type", "standard");
            auto message_dlc        = message.get<uint8_t>("dlc", 0);
            auto message_cycle_time = message.get<uint16_t>("cycle_time", 0);

            uint32_t message_id{0};
            can::message::Format format{can::message::Format::Standard};
            if(message_type_str == "standard")
            {
                std::stringstream ss{};
                ss << message_id_str;
                ss >> std::hex >> message_id;
            }
            else
            {
                std::stringstream ss{};
                ss << message_id_str;
                ss >> std::hex >> message_id;
                format = can::message::Format::Standard;
            }

            can::message m{message_id, message_name, message_dlc, message_cycle_time, format};


            auto variables          = message.get_child("variables");
            for(auto variable_iter : variables)
            {
                auto variable = variable_iter.second;
                auto variable_type      = variable.get<std::string>("type", "");
                auto variable_name      = variable.get<std::string>("name", "");
                auto variable_phys_unit = variable.get<std::string>("phys_unit", "");
                auto variable_enum_name = variable.get<std::string>("enum_name", "");

                if(variable_type == "bit")
                {
                    auto variable_start     = variable.get<uint8_t>("start", 0);
                    can::variable var{can::bit_variable{variable_start}, variable_name, variable_phys_unit, variable_enum_name};
                    m.insert(var);
                }
                
                else if(variable_type == "char")
                {
                    auto variable_start     = variable.get<uint8_t>("start", 0);
                    auto variable_endian    = variable.get<std::string>("endian", "intel");

                    if(variable_endian == "intel")
                    {
                        can::variable var{char_variable{variable_start, can::Endianess::Intel}, variable_name, variable_phys_unit, variable_enum_name};
                        m.insert(var);                    
                    }
                    else if(variable_endian == "motorola")
                    {
                        can::variable var{char_variable{variable_start, can::Endianess::Motorola}, variable_name, variable_phys_unit, variable_enum_name};
                        m.insert(var);
                    }
                    else
                    {
                        can::variable var{char_variable{variable_start, can::Endianess::Intel}, variable_name, variable_phys_unit, variable_enum_name};
                        m.insert(var);
                    }
                }
                
                else if(variable_type == "float")
                {
                    auto variable_start     = variable.get<uint8_t>("start", 0);
                    auto variable_factor    = variable.get<float>("factor", 0.0);
                    auto variable_offset    = variable.get<float>("offset", 0.0);
                    auto variable_endian    = variable.get<std::string>("endian", "intel");
                    
                    if(variable_endian == "intel")
                    {
                        can::variable var{float_variable{variable_start, variable_factor, variable_offset, can::Endianess::Intel}, variable_name, variable_phys_unit, variable_enum_name};
                        m.insert(var);
                    }
                    else if(variable_endian == "motorola")
                    {
                        can::variable var{float_variable{variable_start, variable_factor, variable_offset, can::Endianess::Motorola}, variable_name, variable_phys_unit, variable_enum_name};
                        m.insert(var);
                    }
                    else
                    {
                        can::variable var{float_variable{variable_start, variable_factor, variable_offset, can::Endianess::Intel}, variable_name, variable_phys_unit, variable_enum_name};
                        m.insert(var);
                    }
                }

                else if(variable_type == "double")
                {
                    auto variable_start     = variable.get<uint8_t>("start", 0);
                    auto variable_factor    = variable.get<double>("factor", 0.0);
                    auto variable_offset    = variable.get<double>("offset", 0.0);
                    auto variable_endian    = variable.get<std::string>("endian", "intel");
                    
                    if(variable_endian == "intel")
                    {
                        can::variable var{double_variable{variable_start, variable_factor, variable_offset, can::Endianess::Intel}, variable_name, variable_phys_unit, variable_enum_name};
                        m.insert(var);
                    }
                    else if(variable_endian == "motorola")
                    {
                        can::variable var{double_variable{variable_start, variable_factor, variable_offset, can::Endianess::Motorola}, variable_name, variable_phys_unit, variable_enum_name};
                        m.insert(var);
                    }
                    else
                    {
                        can::variable var{double_variable{variable_start, variable_factor, variable_offset, can::Endianess::Intel}, variable_name, variable_phys_unit, variable_enum_name};
                        m.insert(var);
                    }
                }

                else if(variable_type == "signed")
                {
                    auto variable_start     = variable.get<uint8_t>("start", 0);
                    auto variable_length    = variable.get<uint8_t>("length", 0);
                    auto variable_factor    = variable.get<double>("factor", 0.0);
                    auto variable_offset    = variable.get<double>("offset", 0.0);
                    auto variable_endian    = variable.get<std::string>("endian", "intel");
                    
                    if(variable_endian == "intel")
                    {
                        can::variable var{signed_variable{variable_start, variable_length, variable_factor, variable_offset, can::Endianess::Intel}, variable_name, variable_phys_unit, variable_enum_name};
                        m.insert(var);
                    }
                    else if(variable_endian == "motorola")
                    {
                        can::variable var{signed_variable{variable_start, variable_length, variable_factor, variable_offset, can::Endianess::Motorola}, variable_name, variable_phys_unit, variable_enum_name};
                        m.insert(var);
                    }
                    else
                    {
                        can::variable var{signed_variable{variable_start, variable_length, variable_factor, variable_offset, can::Endianess::Intel}, variable_name, variable_phys_unit, variable_enum_name};
                        m.insert(var);
                    }
                }

                else if(variable_type == "string")
                {
                    auto variable_start     = variable.get<uint8_t>("start", 0);
                    auto variable_length    = variable.get<uint8_t>("length", 0);
                    auto variable_endian    = variable.get<std::string>("endian", "intel");
                    
                    if(variable_endian == "intel")
                    {
                        can::variable var{string_variable{variable_start, variable_length, can::Endianess::Intel}, variable_name, variable_phys_unit, variable_enum_name};
                        m.insert(var);
                    }
                    else if(variable_endian == "motorola")
                    {
                        can::variable var{string_variable{variable_start, variable_length, can::Endianess::Motorola}, variable_name, variable_phys_unit, variable_enum_name};
                        m.insert(var);
                    }
                    else
                    {
                        can::variable var{string_variable{variable_start, variable_length, can::Endianess::Intel}, variable_name, variable_phys_unit, variable_enum_name};
                        m.insert(var);
                    }
                }

                else if(variable_type == "unsigned")
                {
                    auto variable_start     = variable.get<uint8_t>("start", 0);
                    auto variable_length    = variable.get<uint8_t>("length", 0);
                    auto variable_factor    = variable.get<double>("factor", 0.0);
                    auto variable_offset    = variable.get<double>("offset", 0.0);
                    auto variable_endian    = variable.get<std::string>("endian", "intel");
                    
                    if(variable_endian == "intel")
                    {
                        can::variable var{unsigned_variable{variable_start, variable_length, variable_factor, variable_offset, can::Endianess::Intel}, variable_name, variable_phys_unit, variable_enum_name};
                        m.insert(var);
                    }
                    else if(variable_endian == "motorola")
                    {
                        can::variable var{unsigned_variable{variable_start, variable_length, variable_factor, variable_offset, can::Endianess::Motorola}, variable_name, variable_phys_unit, variable_enum_name};
                        m.insert(var);
                    }
                    else
                    {
                        can::variable var{unsigned_variable{variable_start, variable_length, variable_factor, variable_offset, can::Endianess::Intel}, variable_name, variable_phys_unit, variable_enum_name};
                        m.insert(var);
                    }
                }

                else if(variable_type == "raw")
                {
                    auto variable_start     = variable.get<uint8_t>("start", 0);
                    auto variable_length    = variable.get<uint8_t>("length", 0);
                    can::variable var{raw_variable{variable_start, variable_length}, variable_name, variable_phys_unit, variable_enum_name};
                    m.insert(var);
                }

                else
                {

                }
            }
            this->_messages.insert(std::make_pair(m.can_id(), std::move(m)));
        }

        auto enums = root.get_child("enums");
        for(auto enum_iter : enums)
        {
            auto _enum          = enum_iter.second;
            auto enum_name      = _enum.get<std::string>("name", "");

            var_enum var{enum_name};
            
            auto values         = _enum.get_child("values");
            for(auto value_iter : values)
            {
                auto value      = value_iter.second;
                auto type       = value.get<std::string>("type", "bool");
                auto content    = value.get<std::string>("enum", ""); 

                if(type == "bool")
                {
                    auto bool_value = value.get<bool>("value", false);
                    var.insert(bool_value, content);
                }
                else if(type == "char")
                {
                    auto char_value = value.get<char>("value", ' ');
                    var.insert(char_value, content);
                }
                else if(type == "float")
                {
                    auto float_value = value.get<float>("value", 0.0);
                    var.insert(float_value, content);
                }
                else if(type == "double")
                {
                    auto double_value = value.get<double>("value", 0.0);
                    var.insert(double_value, content);
                }
                else if(type == "string")
                {
                    auto string_value = value.get<std::string>("value", "");
                    var.insert(string_value, content);
                }
                else if(type == "uint64_t")
                {
                    auto uint64_t_value = value.get<uint64_t>("value", 0);
                    var.insert(uint64_t_value, content);
                }
            }
            this->_enums.insert(std::make_pair(var.name(), std::move(var)));
        }
    }

    json::json(const json& j)
        :   _messages(j.messages()), _enums{j.enums()}
    {}

    json::json(json&& j)
        :   _messages{std::move(j._messages)}, _enums{std::move(j._enums)}
    {}

    const json::message_type& json::messages() const
    {
        return this->_messages;
    }

    const json::enum_type& json::enums() const
    {
        return this->_enums;
    }

    void swap(json& j1, json& j2)
    {
        std::swap(j1._messages, j2._messages);
        std::swap(j1._enums, j2._enums);
    }
}