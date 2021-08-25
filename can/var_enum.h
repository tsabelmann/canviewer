#ifndef VAR_ENUM_H
#define VAR_ENUM_H

#include <map>
#include <string>
#include <variant>
#include <optional>

namespace can
{
    class var_enum
    {
        public:
            using first_type    = std::variant<bool, char, double, float, std::string, uint64_t>;
            using second_type   = std::string;
            using map_type      = std::map<first_type, second_type>;
            using opt_string    = std::optional<std::string>;

            var_enum() = delete;
            var_enum(std::string name);
            var_enum(const var_enum& e);
            var_enum(var_enum&& e);
            ~var_enum() = default;

            //operator=
            template<typename T>
            var_enum& operator=(T&& e)
            {
                var_enum temp{std::forward<T>(e)};
                swap(temp, *this);
                return *this;
            }
            friend void swap(var_enum& e1, var_enum& e2);

            //insert
            var_enum& insert(bool b, std::string content);
            var_enum& insert(char c, std::string content);
            var_enum& insert(double d, std::string content);
            var_enum& insert(float f, std::string content);
            var_enum& insert(std::string s, std::string content);
            var_enum& insert(uint64_t i, std::string content);
            var_enum& insert(first_type v, std::string content);

            //access (lookup)
            opt_string operator[](bool b) const;
            opt_string operator[](char c) const;
            opt_string operator[](double d) const;
            opt_string operator[](float f) const;
            opt_string operator[](std::string s) const;
            opt_string operator[](uint64_t i) const;
            opt_string operator[](first_type v) const;

            //member access
            const std::string& name() const;
            const map_type& values() const;
            
        private:
            std::string _name;
            map_type _values;
    };

    void swap(var_enum& e1, var_enum& e2);
}

#endif