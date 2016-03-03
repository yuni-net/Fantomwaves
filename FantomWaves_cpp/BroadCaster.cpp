#include <fw_BroadCaster.h>
#include <fw_NetWork.h>
#include <fw_cast.h>
#include <fw_zeromemory.h>
#include "fw_Bindata.h"


namespace fw
{
	unsigned short BroadCaster::get_port() const
	{
		return ntohs(addr.sin_port);
	}



	bool BroadCaster::send(const unsigned short port, const Bindata & data) const
	{
		const NetSurfer target(IP(255, 255, 255, 255), port);

		const int send_len = sendto(
			sock,
			data.buffer(),
			data.bytes(),
			0,
			target.get_address_pointer(),
			target.get_address_bytes());

		return send_len >= int(data.bytes());
	}

	bool BroadCaster::are_there_any_left_datas() const
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

	bool BroadCaster::pop_received_data(Bindata & buffer, NetSurfer & cliant_info)
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


	BroadCaster::BroadCaster()
	{
		sock = INVALID_SOCKET;
		if (NetWork::init_ifneed() == false){ return; }
		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		static const BOOL yes = 1;
		setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *) &yes, sizeof(yes));
	}
	BroadCaster::~BroadCaster()
	{
		if (sock != INVALID_SOCKET)
		{
			closesocket(sock);
			sock = INVALID_SOCKET;
		}
	}


	int BroadCaster::get_received_bytes() const
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