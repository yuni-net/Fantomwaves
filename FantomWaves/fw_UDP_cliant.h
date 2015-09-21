#pragma once

#include "fw_includes.h"
#include "fw_thread.h"
#include "fw_Array.h"
#include "fw_Bindata.h"
#include "fw_NetSurfer.h"

namespace fw
{

	class UDP_cliant
	{
	public:
		bool init(const NetSurfer & server_info);
		bool send(const Bindata & data) const;
		bool did_receive() const;
		bool pop_received_data(Bindata & data);







		// example
#if 0
		fw::NetSurfer server_info(address, port);
		fw::UDP_cliant cliant;
		cliant.set_server_info(server_info);

		fw::Bindata data;
		set_data(data);
		cliant.send(data);

		while (true)
		{
			show_connecting_anime();
			if (cliant.did_receive())
			{
				std::string data;
				cliant.pop_received_data(data);
				// todo
			}

		}
#endif

		UDP_cliant();
		~UDP_cliant();
	private:
		SOCKET sock;
		NetSurfer server_info;

		int get_received_bytes() const;
		bool create_socket_ifneed();
	};
}