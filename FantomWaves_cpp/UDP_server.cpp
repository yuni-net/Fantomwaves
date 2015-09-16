#include <fw_UDP_server.h>
#include <fw_NetWork.h>
#include <fw_zeromemory.h>

namespace fw
{
	bool UDP_server::start_server(const unsigned short port)
	{
		this->port = port;

		NetWork::init_ifneed();
		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		did_create_socket = true;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
		const int result = bind(sock, reinterpret_cast<sockaddr *>(&addr), sizeof(sockaddr_in));
		if (result == -1)
		{
			return false;
		}
		return true;
	}

	/**
	@return
	true: まだ取り出されていないデータがある。
	false: 全てのデータは既に取り出されている。
	*/
	bool UDP_server::are_there_any_left_datas() const
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
			if (result == time_is_out)
			{
				return false;
			}

			const int data_was_NOT_received = 0;
			if (FD_ISSET(sock, &fds) == data_was_NOT_received)
			{
				return false;
			}

			return true;
		}
		return false;
	}

	int UDP_server::get_received_info(sockaddr_in & addr)
	{
		zeromemory(&addr);
		int addr_len = sizeof(sockaddr_in);
		char damy;
		return recvfrom(
			sock,
			&damy,
			0,
			MSG_PEEK | MSG_TRUNC,
			reinterpret_cast<sockaddr *>(&addr),
			&addr_len);
	}

	/**
	@brief 未取り出しの受信データから最も古いものを取り出す。
	@param 取り出したデータを格納するBindata型変数を指定する。
	@return
	true: データを取り出した。
	false: データを取り出さなかった。(未取り出しデータが無かった)
	*/
	bool UDP_server::pop_received_data(Bindata & buffer, NetSurfer & cliant_info)
	{
		if (are_there_any_left_datas() == false)
		{
			return false;
		}

		const int data_bytes = get_received_info(cliant_info.addr);
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

	void UDP_server::add_cliant(const NetSurfer & cliant_info)
	{
		// todo
	}
	void UDP_server::remove_cliant(const NetSurfer & cliant_info)
	{
		// todo
	}

	bool UDP_server::send_a_cliant(const Bindata & data, const NetSurfer & cliant_info) const
	{
		// todo
	}
	bool UDP_server::send_a_cliant(const Bindata & data) const
	{
		// todo
	}
	bool UDP_server::send_all(const Bindata & data) const
	{
		// todo
	}

	void UDP_server::begin_enum_cliants()
	{
		// todo
	}
	bool UDP_server::did_finish_enum() const
	{
		// todo
	}
	void UDP_server::goto_next_cliant()
	{
		// todo
	}



	UDP_server::UDP_server()
	{
		did_create_socket = false;
	}
	UDP_server::~UDP_server()
	{
		if (did_create_socket)
		{
			closesocket(sock);
		}
	}

}