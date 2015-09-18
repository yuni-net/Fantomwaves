#include <fw_UDP_server.h>
#include <fw_NetWork.h>
#include <fw_zeromemory.h>
#include <fw_cast.h>
#include <fw_Log.h>

namespace fw
{
	bool UDP_server::start_server(const unsigned short port)
	{
		this->port = port;
		if (NetWork::init_ifneed() == false){ return false; }

		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (sock == INVALID_SOCKET)
		{
			Log::write("server: failed to create socket");
			return false;
		}
		else
		{
			Log::write("server: succeeded to create socket");
		}

		did_create_socket = true;

		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
		const int result = bind(sock, reinterpret_cast<sockaddr *>(&addr), sizeof(sockaddr_in));
		if (result == -1)
		{ 
			Log::write("server: failed to bind port");
			return false; 
		}
		else
		{
			Log::write("server: succeeded to bind port");
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
			if (result == time_is_out) { return false; }

			const int data_was_NOT_received = 0;
			if (FD_ISSET(sock, &fds) == data_was_NOT_received) { return false; }

			Log::write("server: there are any left datas");

			return true;
		}
		return false;
	}

	int UDP_server::get_received_bytes()
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

	void UDP_server::add_cliant(const NetSurfer & cliant_info)
	{
		cliant_list.push_back(cliant_info);
	}
	void UDP_server::remove_cliant(const NetSurfer & cliant_info)
	{
		for (auto rator = cliant_list.begin(); rator != cliant_list.end(); ++rator)
		{
			const sockaddr_in & now_addr = (*rator).addr;
			const sockaddr_in & cliant_addr = cliant_info.addr;
			if (now_addr.sin_addr.S_un.S_addr == cliant_addr.sin_addr.S_un.S_addr)
			{
				cliant_list.erase(rator);
				return;
			}
		}
	}

	bool UDP_server::send_a_cliant(const Bindata & data, const NetSurfer & cliant_info) const
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
	bool UDP_server::send_a_cliant(const Bindata & data) const
	{
		const NetSurfer & cliant_info = *current_cliant;
		return send_a_cliant(data, cliant_info);
	}
	bool UDP_server::send_all(const Bindata & data) const
	{
		bool did_succeed = true;
		for (auto rator = cliant_list.begin(); rator != cliant_list.end(); ++rator)
		{
			if (send_a_cliant(data, *rator) == false)
			{
				did_succeed = false;
			}
		}

		return did_succeed;
	}
	bool UDP_server::send_all_except(const NetSurfer & excepted_cliant, const  Bindata & data) const
	{
		bool did_succeed = true;
		for (auto rator = cliant_list.begin(); rator != cliant_list.end(); ++rator)
		{
			if ((*rator) == excepted_cliant) { continue; }

			if (send_a_cliant(data, *rator) == false)
			{
				did_succeed = false;
			}
		}

		return did_succeed;
	}

	void UDP_server::begin_enum_cliants()
	{
		current_cliant = cliant_list.begin();
	}
	bool UDP_server::did_finish_enum() const
	{
		return current_cliant == cliant_list.end();
	}
	void UDP_server::goto_next_cliant()
	{
		++current_cliant;
	}



	UDP_server::UDP_server()
	{
		did_create_socket = false;
		current_cliant = cliant_list.begin();
	}
	UDP_server::~UDP_server()
	{
		if (did_create_socket)
		{
			closesocket(sock);
		}
	}

}