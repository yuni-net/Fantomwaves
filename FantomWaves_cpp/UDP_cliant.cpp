#include <fw_includes.h>
#include <fw_UDP_cliant.h>
#include <fw_NetWork.h>
#include <fw_zeromemory.h>

namespace fw
{
	void UDP_cliant::connect_server(const unsigned short port, const Bindata & data, const int limit_time)
	{
		this->port = port;
		this->limit_time = limit_time;

		NetWork::init_ifneed();
		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

		int perm = 1;
		setsockopt(sock, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<const char *>(&perm), sizeof(int));

		set_addr_for_broadcast();
		send_data(data);
	}

	bool UDP_cliant::did_timeout() const
	{
		// todo
	}

	bool UDP_cliant::did_receive() const
	{
		// todo
	}

	unsigned int UDP_cliant::num_received_datas() const
	{
		// todo
	}

	Bindata UDP_cliant::pop_received_data()
	{
		// todo
	}

	void UDP_cliant::set_server_IP(const IP & server_IP)
	{
		this->server_IP = server_IP;
		addr.sin_addr.s_addr = inet_addr(server_IP.to_ccharp());
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


}