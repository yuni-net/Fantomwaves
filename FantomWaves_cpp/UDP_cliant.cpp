#include <fw_includes.h>
#include <fw_UDP_cliant.h>
#include <fw_NetWork.h>
#include <fw_zeromemory.h>
#include <fw_cast.h>

namespace fw
{
	void UDP_cliant::connect_server(
		const unsigned short port,
		const Bindata & data,
		const int limit_time,
		const Bindata & server_response)
	{
		this->port = port;
		this->limit_time = limit_time;
		this->server_response = server_response;
		received_datas.set_size(20);

		NetWork::init_ifneed();
		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

		int perm = 1;
		setsockopt(sock, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<const char *>(&perm), sizeof(int));

		set_addr_for_broadcast();
		send_data(data);

		did_timeout_ = false;
		did_connect_server_ = false;
		thread_.begin(find_server, this);
	}

	bool UDP_cliant::did_timeout() const
	{
		return did_timeout_;
	}

	bool UDP_cliant::did_connect_server() const
	{
		return did_connect_server_;
	}

	bool UDP_cliant::did_receive() const
	{
		return num_received_datas() > 0;
	}

	unsigned int UDP_cliant::num_received_datas() const
	{
		return received_datas.size();
	}

	Bindata UDP_cliant::pop_received_data()
	{
		return received_datas.pop();
	}


	bool UDP_cliant::send(const Bindata & data)
	{
		int send_len = sendto(
			sock,
			data.buffer(),
			data.byte(),
			0,
			reinterpret_cast<sockaddr *>(&addr),
			sizeof(sockaddr_in));

		return send_len >= data.byte();
	}

	const IP & UDP_cliant::get_server_IP() const
	{
		return server_IP;
	}

	unsigned short UDP_cliant::get_server_port() const
	{
		return port;
	}




	UDP_cliant::UDP_cliant()
	{
		did_create_socket = false;
		is_connecting_server_ = true;
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


	fw_thread_ UDP_cliant::find_server(void * param)
	{
		UDP_cliant & net = *pointer_cast<UDP_cliant *>(param);

		sockaddr_in their_addr;
		const int addr_len = sizeof(sockaddr_in);

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
				break;
			}

			const int NOT_received = 0;
			if (FD_ISSET(net.sock, &fds) == 0)
			{
				continue;
			}

			memset(message, 0, 1024);
			recvfrom(
				com_sock,
				message,
				1024,
				0,
				reinterpret_cast<sockaddr *>(&cliant_addr),
				&addr_len);

			std::cout << "You received a message:" << std::endl;
			for (int i = 0; i < 48; ++i)
			{
				char code_str[256];
				itoa(message[i], code_str, 10);
				std::cout << message[i] << " (" << code_str << ")" << std::endl;
			}

			if (is_the_address_mine(cliant_addr.sin_addr.S_un.S_addr))
			{
				// 自分自身からのメッセージは無視する
				std::cout << "It's from my self." << std::endl;
				continue;
			}

			if (process_message(message, cliant_addr))
			{
				return 1;
			}
		}

		return 0;
	}

}