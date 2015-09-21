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

		// example
#if 0
		fw::P2P p2p;
		const bool did_succeed = p2p.start();
		const unsigned short port = p2p.get_port();
		const unsigned long address;
		set_address(address);
		fw::NetSurfer surfer(address, port);
		fw::Bindata data;
		set_data(data);
		p2p.send(surfer, data);
		while (p2p.are_there_any_left_datas())
		{
			fw::Bindata data;
			fw::NetSurfer serfer;
			p2p.pop_received_data(data, serfer);
		}
#endif


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