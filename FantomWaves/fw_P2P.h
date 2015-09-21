#pragma once

#include "fw_includes.h"
#include "fw_NetSurfer.h"
#include "fw_Bindata.h"

namespace fw
{
	class P2P
	{
	public:
		bool start();
		unsigned short get_port() const;
		bool send(const NetSurfer & surfer, const Bindata & data) const;
		bool are_there_any_left_datas() const;
		bool pop_received_data(Bindata & data, NetSurfer & surfer);



		P2P();
		~P2P();
	private:
		SOCKET sock;
		bool did_create_socket;
		sockaddr_in addr;
		unsigned short port;


		int get_received_bytes() const;

	};
}