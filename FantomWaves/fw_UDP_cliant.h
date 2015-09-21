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
		void set_server_info(const NetSurfer & server_info);
		bool send(const Bindata & data) const;
		bool did_receive() const;
		bool pop_received_data(Bindata & data);

		void wait_receive() const;
		void wait_receive(unsigned long interval) const;






		// example
#if 0
		fw::NetSurfer server_info(address, port);
		fw::UDP_cliant cliant;
		cliant.set_server_info(server_info);

		std::string data;
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

			// ��������
#if 0
			cliant.wait_receive();
			std::string data;
			cliant.pop_received_data(data);
			// todo
#endif
		}
#endif

		UDP_cliant();
		~UDP_cliant();
	private:
		bool did_create_socket;
		SOCKET sock;
		NetSurfer server_info;

		int get_received_bytes() const;
	};
}