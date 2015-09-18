#include <fw_includes.h>
#include <fw_UDP_cliant.h>
#include <fw_NetWork.h>
#include <fw_zeromemory.h>
#include <fw_cast.h>
#include <fw_Log.h>

namespace fw
{
	bool UDP_cliant::connect_server(
		const unsigned short port,
		const Bindata & data,
		const int limit_time,
		const Bindata & server_response)
	{
		this->port = port;
		this->limit_time = limit_time;
		this->server_response = server_response;
		if (NetWork::init_ifneed() == false) { return false; }

		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (sock == INVALID_SOCKET)
		{
			Log::write("cliant: failed to create socket");
			return false;
		}
		else
		{
			Log::write("cliant: succeeded to create socket");
		}

		const int perm = 1;	// 必ずintである必要がある。
		const int result = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<const char *>(&perm), sizeof(int));
		const int error = -1;
		if (result == error)
		{
			Log::write("cliant: failed to setsockopt");
			return false;
		}
		else
		{
			Log::write("cliant: succeeded to setsockopt");
		}

		set_addr_for_broadcast();
		send(data);
		Log::write("cliant: broadcast was send");

		did_timeout_ = false;
		did_connect_server_ = false;
		newthread(find_server, this);
		return true;
	}

	bool UDP_cliant::did_timeout() const
	{
		return did_timeout_;
	}

	bool UDP_cliant::did_connect_server() const
	{
		return did_connect_server_;
	}

	bool UDP_cliant::are_there_any_left_datas() const
	{
		sockaddr_in their_addr;
		int data_bytes;
		return get_received_info(their_addr, data_bytes);
	}

	bool UDP_cliant::get_received_info(sockaddr_in & their_addr, int & data_bytes) const
	{
		while (true)
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

			Log::write("cliant: a message was received");

			zeromemory(&their_addr);
			char damy;
			int addr_len = sizeof(sockaddr_in);
			data_bytes = recvfrom(
				sock,
				&damy,
				0,
				MSG_PEEK | MSG_TRUNC,
				reinterpret_cast<sockaddr *>(&their_addr),
				&addr_len);

			if (data_bytes <= 0) { continue; }

			if (their_addr.sin_addr.S_un.S_addr != addr.sin_addr.S_un.S_addr)
			{
				Log::write("cliant: that address is self address");
				continue;
			}

			return true;
		}
		return false;
	}

	bool UDP_cliant::pop_received_data(Bindata & buffer)
	{
		sockaddr_in their_addr;
		int data_bytes;
		const bool can_I_pop = get_received_info(their_addr, data_bytes);
		if (can_I_pop == false) { return false; }

		buffer.set_size(data_bytes);
		const int received_bytes = recvfrom(
			sock,
			buffer.buffer(),
			buffer.bytes(),
			MSG_TRUNC,
			NULL,
			NULL);

		return true;
	}

	bool UDP_cliant::send(const Bindata & data) const
	{
		const int send_len = sendto(
			sock,
			data.buffer(),
			data.bytes(),
			0,
			reinterpret_cast<const sockaddr *>(&addr),
			sizeof(sockaddr_in));

		return send_len >= int(data.bytes());
	}

#if 0
	const IP & UDP_cliant::get_server_IP() const
	{
		return server_IP;
	}
#endif

	unsigned short UDP_cliant::get_server_port() const
	{
		return port;
	}




	UDP_cliant::UDP_cliant()
	{
		did_create_socket = false;
	}
	UDP_cliant::~UDP_cliant()
	{
		if (did_create_socket)
		{
			closesocket(sock);
		}
	}



	void UDP_cliant::set_addr_for_broadcast()
	{
		zeromemory(&addr);
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr("255.255.255.255");
		addr.sin_port = htons(port);
	}


	void UDP_cliant::find_server(void * param)
	{
		UDP_cliant & net = *pointer_cast<UDP_cliant *>(param);

		fd_set fds, readfds;
		FD_ZERO(&readfds);
		FD_SET(net.sock, &readfds);

		timeval timev;
		timev.tv_sec = net.limit_time;
		timev.tv_usec = 0;

		while (true)
		{
			memcpy(&fds, &readfds, sizeof(fd_set));
			const int result = select(0, &fds, NULL, NULL, &timev);
			const int time_is_out = 0;
			if (result == time_is_out)
			{
				Log::write("cliant: server was not found cuz timeout");
				net.did_timeout_ = true;
				return;
			}

			const int data_was_NOT_received = 0;
			if (FD_ISSET(net.sock, &fds) == data_was_NOT_received)
			{
				Sleep(15);
				continue;
			}

			Log::write("cliant: You received a response for broadcast");

			sockaddr_in their_addr;
			zeromemory(&their_addr);
			int addr_len = sizeof(sockaddr_in);
			Bindata response;
			response.set_size(net.server_response.bytes());

			const int received_bytes = recvfrom(
				net.sock,
				response.buffer(),
				response.bytes(),
				MSG_TRUNC,
				reinterpret_cast<sockaddr *>(&their_addr),
				&addr_len);

			if (received_bytes != net.server_response.bytes())
			{
				Log::write("cliant: size of received data was unexpected");
				// データサイズが想定外ということはサーバーから送られてきたデータではない
				continue;
			}

			if (NetWork::is_my_address(their_addr.sin_addr.S_un.S_addr))
			{
				Log::write("cliant: that is self address");
				// 自分自身からのメッセージは無視する
				continue;
			}

			if (response != net.server_response)
			{
				Log::write("cliant: that is NOT server's response");
				continue;
			}

			net.addr.sin_addr.S_un.S_addr = their_addr.sin_addr.S_un.S_addr;
#if 0
			途中でアドレスを変更しても意味がないかもしれない。
			connectやacceptを使う必要があるかもしれない。
#endif
		//	net.server_IP.set(inet_ntoa(net.addr.sin_addr));
			net.did_connect_server_ = true;
			return;
		}
	}

}