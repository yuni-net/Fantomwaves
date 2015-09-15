#pragma once

#include <fw_includes.h>
#include <fw_thread.h>
#include <fw_Array.h>

namespace fw
{
	class Bindata;

	class UDP_cliant
	{
	public:

		/**
		 @brief �T�[�o�[�ւ̐ڑ����J�n����B
		 @param
		      port: �|�[�g�ԍ����w�肷��B
			  data: ���������K�̃N���C�A���g�ł��邱�Ƃ��ؖ�����f�[�^���w�肷��B
			  limit_time: �T�[�o�[����̉�����҂������Ԃ�b���Ŏw�肷��B
			  server_response: ����Ԃ���Ă����f�[�^������ƈ�v����΁A������T�[�o�[�Ƃ݂Ȃ��B
		 */
		void connect_server(
			const unsigned short port,
			const Bindata & data,
			const int limit_time,
			const Bindata & server_response);

		/**
		 @return
		      true: �������Ԉȓ��ɃT�[�o�[��������Ȃ������B
			  false: �܂��������ԂɒB���Ă��Ȃ����A���ɃT�[�o�[���������Ă���B
		 */
		bool did_timeout() const;

		/**
		 @return
		      true: �T�[�o�[�ɐڑ������B
			  false: �T�[�o�[�ɐڑ����Ă��Ȃ��B
		 */
		bool did_connect_server() const;

		/**
		 @return
		      true: ��M�����f�[�^������A�܂����o����Ă��Ȃ���Ԃł���B
			  false: ��M�����f�[�^�͖����B
		 */
		bool did_receive() const;

		/**
		 @return �܂����o����Ă��Ȃ���M�f�[�^�̐����Ԃ�B
		 */
		unsigned int num_received_datas() const;

		/**
		 @return �����o���̎�M�f�[�^����ł��Â����̂����o���ĕԂ��B
		 */
		Bindata pop_received_data();

		/**
		 @brief �T�[�o�[�Ƀf�[�^�𑗐M����B
		 @param ���M�������f�[�^���w�肷��B
		 */
		bool send(const Bindata & data) const;

		/**
		 @return �T�[�o�[��IP�A�h���X��Ԃ��B
		 */
		const IP & get_server_IP() const;

		/**
		 @return �T�[�o�[�̃|�[�g�ԍ���Ԃ��B
		 */
		unsigned short get_server_port() const;


		// example
#if 0
		fw::UDP_cliant net;
		net.connect_server(port, data, limit_time, server_response);

		while (main_loop)
		{
			if(net.did_timeout())
			{
				process_when_not_found_server();
			}

			if(net.did_connect_server() == false)
			{
				show_connecting_animation();
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
		Bindata server_response;
		fw::Thread thread_;
		bool did_timeout_;
		bool did_connect_server_;
		RingQue<Bindata> received_datas;



		void set_addr_for_broadcast();

		/**
		 @return
		     true: succeeded
			 false: failed
		 */
		bool send_data(const Bindata & data);

		static fw_thread_ find_server(void * param);
	};
}