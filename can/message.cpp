#include "message.h"

namespace can
{
    message::message(uint32_t can_id, std::string name, uint8_t dlc, uint16_t cycle_time, message::Format format)
        :   _can_id{can_id}, _name{name}, _dlc{dlc}, _cycle_time{cycle_time}, _format{format}, _variables{}
    {
        if(this->_format == message::Format::Standard)
            this->_can_id &= 0x7FF;
        else
            this->_can_id &= 0x1FFFFFFF;
    }

    message::message(const message& message)
        :   _can_id{message.can_id()}, _name{message.name()}, _dlc{message.dlc()}, _cycle_time{message.cycle_time()}, _format{message.format()}
    {
        for(const auto& data : message.variables())
        {
            this->_variables.insert(std::make_pair(data.first, data.second));
        }
    }

    message::message(message&& message)
        :   _can_id{std::move(message._can_id)}, _name{std::move(message._name)}, _dlc{std::move(message._dlc)}, _cycle_time{std::move(message._cycle_time)}, _format{std::move(message._format)}, _variables{std::move(message._variables)}
    {}

    //member access
    const uint32_t& message::can_id() const
    {
        return this->_can_id;
    }

    const std::string& message::name() const
    {
        return this->_name;
    }

    const uint8_t& message::dlc() const
    {
        return this->_dlc;
    }

    const uint16_t& message::cycle_time() const
    {
        return this->_cycle_time;
    }

    const message::Format& message::format() const
    {
        return this->_format;
    }

    message::map_type& message::variables()
    {
        return this->_variables;
    }

    const message::map_type& message::variables() const
    {
        return this->_variables;
    }

    //insert
    message& message::insert(variable v)
    {
        this->_variables.insert(std::make_pair(v.name(), std::move(v)));
        return *this;
    }

    message::opt_variable message::operator[](std::string name) const
    {
        auto found = this->_variables.find(name);
        if(found != this->_variables.end())
        {
            return found->second;
        }
        else
        {
            return{};
        }
    }

    //swap
    void swap(message& m1, message& m2)
    {
        std::swap(m1._can_id, m2._can_id);
        std::swap(m1._name, m2._name);
        std::swap(m1._cycle_time, m2._cycle_time);
        std::swap(m1._format, m2._format);
        std::swap(m1._variables, m2._variables);
    }
}