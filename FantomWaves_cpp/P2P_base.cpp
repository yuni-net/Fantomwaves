#include <fw_P2P_base.h>
#include <fw_NetWork.h>
#include <fw_cast.h>
#include <fw_zeromemory.h>
#include "fw_Bindata.h"


namespace fw
{
	unsigned short P2P_base::get_port() const
	{
		return ntohs(addr.sin_port);
	}



	bool P2P_base::send(const NetSurfer & cliant_info, const Bindata & data) const
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

	bool P2P_base::are_there_any_left_datas() const
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

	bool P2P_base::pop_received_data(Bindata & buffer, NetSurfer & cliant_info)
	{
		if (are_there_any_left_datas() == false)
		{
			return false;
		}

		buffer.set_size(65536);
		sockaddr_in cliant_addr;
		int addr_len = sizeof(sockaddr_in);
		const int received_bytes = recvfrom(
			sock,
			buffer.buffer(),
			buffer.bytes(),
			0,
			fw::pointer_cast<sockaddr *>(&cliant_addr),
			&addr_len);

		if (received_bytes == -1)
		{
			printf("failed to recvfrom\n");
			int e = WSAGetLastError();
			printf("error_code:"); printf("%d\n", e);
			return false;
		}

		buffer.set_size(received_bytes);
		cliant_info.set_address(cliant_addr);

		return true;
	}


	P2P_base::P2P_base()
	{
		sock = INVALID_SOCKET;
		if (NetWork::init_ifneed() == false){ return; }
		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	}
	P2P_base::~P2P_base()
	{
		if (sock != INVALID_SOCKET)
		{
			closesocket(sock);
			sock = INVALID_SOCKET;
		}
	}


	int P2P_base::get_received_bytes() const
	{
		Bindata buffer;
		buffer.set_size(2048);
		int received_bytes;

		while (true)
		{
			received_bytes = recvfrom(
				sock,
				buffer.buffer(),
				buffer.bytes(),
				MSG_PEEK,
				NULL,
				NULL);

			const int error = -1;
			if (received_bytes != error)
			{
				break;
			}

			const int buffer_overflow = 10040;
			if (WSAGetLastError() != buffer_overflow)
			{
				return error;
			}

			buffer.set_size(buffer.bytes() * 2);
			continue;
		}

		return received_bytes;
	}


}