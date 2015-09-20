#include <fw_P2P.h>
#include <fw_NetWork.h>
#include <fw_cast.h>

namespace fw
{
	bool P2P::start()
	{
		if (NetWork::init_ifneed() == false){ return false; }

		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (sock == INVALID_SOCKET){ return false; }

		did_create_socket = true;

		for (port = min_ephemeral_port; port <= max_ephemeral_port; ++port)
		{
			addr.sin_family = AF_INET;
			addr.sin_port = htons(port);
			addr.sin_addr.S_un.S_addr = INADDR_ANY;
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
			reinterpret_cast<const sockaddr *>(&cliant_info.addr),
			sizeof(sockaddr_in));

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
		int addr_len = sizeof(sockaddr_in);

		const int received_bytes = recvfrom(
			sock,
			buffer.buffer(),
			buffer.bytes(),
			MSG_TRUNC,
			pointer_cast<sockaddr *>(&(cliant_info.addr)),
			&addr_len);

		return true;
	}


	P2P::P2P()
	{
		did_create_socket = false;
	}
	P2P::~P2P()
	{
		if (did_create_socket)
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