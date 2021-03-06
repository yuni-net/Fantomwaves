#include <fw_includes.h>
#include <fw_UDP_cliant.h>
#include <fw_NetWork.h>
#include <fw_zeromemory.h>
#include <fw_cast.h>

namespace fw
{
	bool UDP_cliant::create_socket_ifneed()
	{
		if (sock != INVALID_SOCKET){ return true; }
		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		return sock != INVALID_SOCKET;
	}

	bool UDP_cliant::init(const NetSurfer & server_info)
	{
		this->server_info = server_info;
		if (NetWork::init_ifneed() == false){ return false; }
		if (create_socket_ifneed() == false){ return false; }
		return true;
	}

	bool UDP_cliant::send(const Bindata & data) const
	{
		const int send_len = sendto(
			sock,
			data.buffer(),
			data.bytes(),
			0,
			server_info.get_address_pointer(),
			server_info.get_address_bytes());

		return send_len >= int(data.bytes());
	}

	bool UDP_cliant::did_receive() const
	{
		fd_set fds;
		FD_ZERO(&fds);
		FD_SET(sock, &fds);

		timeval timev;
		timev.tv_sec = 0;
		timev.tv_usec = 8;

		const int result = select(0, &fds, NULL, NULL, &timev);
		const int time_is_out = 0;
		if (result == time_is_out) { return false; }

		const int data_was_NOT_received = 0;
		if (FD_ISSET(sock, &fds) == data_was_NOT_received) { return false; }

		return true;
	}

	bool UDP_cliant::pop_received_data(Bindata & buffer)
	{
		if (did_receive() == false)
		{
			return false;
		}

		const int data_bytes = get_received_bytes();
		buffer.set_size(data_bytes);
		int addr_len = sizeof(sockaddr_in);

		const int received_bytes = recvfrom(
			sock,
			buffer.buffer(),
			buffer.bytes(),
			MSG_TRUNC,
			NULL,
			NULL);

		return true;
	}







	UDP_cliant::UDP_cliant()
	{
		sock = INVALID_SOCKET;
	}
	UDP_cliant::~UDP_cliant()
	{
		if (sock != INVALID_SOCKET)
		{
			closesocket(sock);
		}
	}


	int UDP_cliant::get_received_bytes() const
	{
		char damy;
		return recvfrom(
			sock,
			&damy,
			0,
			MSG_PEEK | MSG_TRUNC,
			NULL,
			NULL);
	}


}





