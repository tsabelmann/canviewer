#ifndef CAN_LINUX_SOCKET_H
#define CAN_LINUX_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include <fcntl.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <memory>

#include "frame.h"


namespace can
{
	class linux_socket
	{
		public:
			linux_socket(std::string interface);
			linux_socket(const linux_socket& s) = delete;
			linux_socket(linux_socket&& s);
			~linux_socket();

			//operator=
			template<typename T>
			linux_socket& operator=(T&& s)
			{
				linux_socket temp{std::forward<T>(s)};
				swap(temp, *this);
				return *this;
			}
			friend void swap(linux_socket& s1, linux_socket& s2);

			//receive
			std::unique_ptr<can::frame> receive();

		private:
			struct ifreq _ifr;
			struct sockaddr_can _addr;
			int _sd;
			std::string _interface;
	};

	void swap(linux_socket& s1, linux_socket& s2);
}

#endif
