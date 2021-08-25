#ifndef MESSAGE_H
#define MESSAGE_H

#include <map>
#include <string>
#include <memory>
#include "variable.h"

namespace can
{
    class message
    {
        public:          
            template<typename K, typename V>
            using map = std::map<K, V>;
            using map_type = map<std::string, variable>;
            using opt_variable = std::optional<variable>;
            
            enum class Format{Standard, Extended};

            message(uint32_t can_id, std::string name, uint8_t dlc, uint16_t cycle_time, Format format);
            message(const message& message);
            message(message&& message);
            ~message() = default;

            //operator=
            template<typename T>
            message& operator=(T&& m)
            {
                message temp{std::forward<T>(m)};
                swap(temp, *this);
                return *this;
            }
            friend void swap(message& m1, message& m2);

            //member access
            const uint32_t& can_id() const;
            const std::string& name() const;
            const uint8_t& dlc() const;
            const uint16_t& cycle_time() const;
            const Format& format() const;

            map_type& variables();
            const map_type& variables() const;

            //insert
            message& insert(variable v);

            //get variables
            opt_variable operator[](std::string) const;

        private:
            uint32_t _can_id;
            std::string _name;
            uint8_t _dlc;
            uint16_t _cycle_time;
            Format _format;
            map_type _variables;
    };

    void swap(message& m1, message& m2);
}

#endif