#ifndef CAN_JSON_H
#define CAN_JSON_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "message.h"
#include "var_enum.h"

namespace can
{
    class json
    {
        public:
            using message_type = std::map<uint32_t, message>;
            using enum_type = std::map<std::string, var_enum>;

            json(std::string path);
            json(const json& j);
            json(json&& j);

            template<typename T>
            json& operator=(T&& j)
            {
                json temp{std::forward<T>(j)};
                swap(temp, *this);
                return *this;
            }
            friend void swap(json& j1, json& j2);

            const message_type& messages() const;
            const enum_type& enums() const;

        private:
            message_type _messages;
            enum_type _enums;
    };

    void swap(json& j1, json& j2);
}

#endif