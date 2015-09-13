#pragma once

#include <fw_includes.h>

namespace fw
{
	class Bindata;

	class UDP_cliant
	{
	public:
		void connect_server(const unsigned short port, const Bindata & data, const int limit_time);
		bool did_timeout() const;
		bool did_receive() const;
		unsigned int num_received_datas() const;
		Bindata pop_received_data();
		void set_server_IP(const IP & server_IP);
		bool send(const Bindata & data) const;

		const IP & get_server_IP() const;
		unsigned short get_server_port() const;


		// example
#if 0
		fw::UDP_cliant net;
		net.connect_server(port, data, limit_time);
		bool is_connecting_server = true;

		while (main_loop)
		{
			if(net.did_timeout())
			{
				process_when_not_found_server();
			}

			if(is_connecting_server)
			{
				show_connecting_animation();
				if(net.did_receive())
				{
					fw::IP server_IP;
					if(is_response_of_server(net.received_data(server_IP))
					{
						net.set_server_IP(server_IP);
						is_connecting_server = true;
					}
				}
			}
			else
			{
				if (net.did_receive())
				{
					for (fw::uint i = 0; i < net.num_received_messages(); ++i)
					{
						fw::Bindata data = net.received_message();
						process(data);
					}
				}

				net.send(data);
			}
		}

#endif

		UDP_cliant();
		~UDP_cliant();
	private:
		bool did_create_socket;
		SOCKET sock;
		unsigned short port;
		IP server_IP;
		int limit_time;
		sockaddr_in addr;



		void set_addr_for_broadcast();

		/**
		 @return
		     true: succeeded
			 false: failed
		 */
		bool send_data(const Bindata & data);
	};
}