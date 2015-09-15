#pragma once

#include "fw_Bindata.h"

namespace fw
{
	class UDP_server
	{
	public:
		bool start_server(const unsigned short port);

		/**
		@return
		true: �܂����o����Ă��Ȃ��f�[�^������B
		false: �S�Ẵf�[�^�͊��Ɏ��o����Ă���B
		*/
		bool are_there_any_left_datas() const;

		/**
		@brief �����o���̎�M�f�[�^����ł��Â����̂����o���B
		@param ���o�����f�[�^���i�[����Bindata�^�ϐ����w�肷��B
		@return
		true: �f�[�^�����o�����B
		false: �f�[�^�����o���Ȃ������B(�����o���f�[�^����������)
		*/
		bool pop_received_data(Bindata & buffer, NetSurfer & cliant_info);

		void add_cliant(const NetSurfer & cliant_info);
		void remove_cliant(const NetSurfer & cliant_info);

		bool send_a_cliant(const Bindata & data, const NetSurfer & cliant_info) const;
		bool send_a_cliant(const Bindata & data) const;
		bool send_all(const Bindata & data) const;

		void begin_enum_cliants();
		bool did_finish_enum() const;
		void goto_next_cliant();


		// example
#if 0
		fw::UDP_server server;
		server.start_server(port);

		while (main_loop)
		{
			while(server.are_there_any_left_datas())
			{
				fw::NetSurfer cliant_info;
				fw::Bindata data;
				server.pop_received_data(data, cliant_info);
				if (is_request_connecting(data))
				{
					server.add_cliant(cliant_info);
				}
				if (is_request_disconnecting(data))
				{
					server.remove_cliant(cliant_info);
				}
				if(todo_response(data))
				{
					server.send_a_cliant(response_data, cliant_info);
				}
			}

			server.send_all(data);

			server.begin_enum_cliants();
			while (server.did_finish_enum() == false)
			{
				server.send_a_cliant(data);
				//	server.send_a_cliant(server.get_cliant_IP(), data);
				server.goto_next_cliant();
			}

#if 0
			// Deprecated
			for (fw::uint i = 0; i < server.num_cliants(); ++i)
			{
				server.send(server.get_cliant_IP(i), data);
				//	server.send(i, data);	
			}
#endif
		}

#endif




		UDP_server();
		~UDP_server();
	private:
		bool did_create_socket;
		SOCKET sock;
		unsigned short port;
	};



}