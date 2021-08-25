#include "linux_socket.h"

namespace can
{
	linux_socket::linux_socket(std::string interface)
		:	_interface{interface}
	{
		this->_sd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
		strcpy(this->_ifr.ifr_name, interface.c_str());
		ioctl(this->_sd, SIOCGIFINDEX, &this->_ifr);
		this->_addr.can_family = AF_CAN;
		this->_addr.can_ifindex = this->_ifr.ifr_ifindex;
		fcntl(this->_sd, F_SETFL, MSG_WAITALL);
		bind(this->_sd, (struct sockaddr*)&(this->_addr), sizeof(this->_addr));
	}

	linux_socket::linux_socket(linux_socket&& s)
		:	_ifr(std::move(s._ifr)), _addr(std::move(s._addr)), _sd(std::move(s._sd)), _interface{std::move(s._interface)}
	{
		memset(&s._ifr, 0, sizeof(s._ifr));
		memset(&s._addr, 0, sizeof(s._addr));
		s._sd = 0;
	}
	
	linux_socket::~linux_socket()
	{
		if(this->_sd)
			close(this->_sd);
	}

	std::unique_ptr<frame> linux_socket::receive()
	{
		can_frame fr;
		auto received = recv(this->_sd, &fr, sizeof(struct can_frame), 0);
		
		if(received >= 0 && received >= sizeof(struct can_frame))
		{
			uint32_t can_id = fr.can_id;
			bool is_extended = can_id & 0x70000000U;
										
			if(is_extended)
			{
				can_id &= 0x1FFFFFFFU;
				return std::make_unique<frame>(can_id, fr.data, fr.can_dlc, can::frame::Format::Extended);
			}
			else
			{
				can_id &= 0x000007FFU;
				return std::make_unique<frame>(can_id, fr.data, fr.can_dlc, can::frame::Format::Standard);
			}
		}
		else
		{
			return {};
		}
	}

	void swap(linux_socket& s1, linux_socket& s2)
	{
		std::swap(s1._ifr, s2._ifr);
		std::swap(s1._addr, s2._addr);
		std::swap(s1._sd, s2._sd);
		std::swap(s1._interface, s2._interface);
	}
}
