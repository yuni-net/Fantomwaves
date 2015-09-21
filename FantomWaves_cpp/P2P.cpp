#include <fw_P2P.h>
#include <fw_NetWork.h>
#include <fw_cast.h>
#include <fw_zeromemory.h>

namespace fw
{
	bool P2P::bind_port_ifneed()
	{
		if (did_bind){ return true; }

		zeromemory(&addr);
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
		for (port = min_ephemeral_port; port <= max_ephemeral_port; ++port)
		{
			addr.sin_port = htons(port);
			const int result = bind(sock, reinterpret_cast<sockaddr *>(&addr), sizeof(sockaddr_in));
			const int error = -1;
			if (result == error)
			{
				if (port == max_ephemeral_port){ return false; }
			}
			else
			{
				break;
			}
		}
		did_bind = true;
		return true;
	}

	bool P2P::create_socket_ifneed()
	{
		if (sock != INVALID_SOCKET){ return true; }
		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		return sock != INVALID_SOCKET;
	}

	bool P2P::start()
	{
		if (NetWork::init_ifneed() == false){ return false; }
		if (create_socket_ifneed() == false){ return false; }
		if (bind_port_ifneed() == false){ return false; }
		return true;
	}

	unsigned short P2P::get_port() const
	{
		return port;
	}

	bool P2P::send(const NetSurfer & cliant_info, const Bindata & data) const
	{
		const int send_len = sendto(
			sock,
			data.buffer(),
			data.bytes(),
			0,
			cliant_info.get_address_pointer(),
			cliant_info.get_address_bytes());

		return send_len >= int(data.bytes());
	}

	bool P2P::are_there_any_left_datas() const
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

	bool P2P::pop_received_data(Bindata & buffer, NetSurfer & cliant_info)
	{
		if (are_there_any_left_datas() == false)
		{
			return false;
		}

		const int data_bytes = get_received_bytes();
		buffer.set_size(data_bytes);
		int addr_len = cliant_info.get_address_bytes();

		const int received_bytes = recvfrom(
			sock,
			buffer.buffer(),
			buffer.bytes(),
			MSG_TRUNC,
			cliant_info.get_address_pointer(),
			&addr_len);

		return true;
	}


	P2P::P2P()
	{
		sock = INVALID_SOCKET;
		did_bind = false;
	}
	P2P::~P2P()
	{
		if (sock != INVALID_SOCKET)
		{
			closesocket(sock);
		}
	}


	int P2P::get_received_bytes() const
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