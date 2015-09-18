#pragma once

#include "fw_includes.h"
#include "fw_thread.h"
#include "fw_Array.h"
#include "fw_Bindata.h"

namespace fw
{

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
		 @return
		      true: ����
			  false: ���s
		 */
		bool connect_server(
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
		bool pop_received_data(Bindata & buffer);

		/**
		 @brief �T�[�o�[�Ƀf�[�^�𑗐M����B
		 @param ���M�������f�[�^���w�肷��B
		 */
		bool send(const Bindata & data) const;

		/**
		 @return �T�[�o�[��IP�A�h���X��Ԃ��B
		 */
	//	const IP & get_server_IP() const;

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
				while (net.are_there_any_left_datas())
				{
					fw::Bindata data;
					net.pop_received_data(data);
					process(data);
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
	//	IP server_IP;
		int limit_time;
		sockaddr_in addr;
		Bindata server_response;
		bool did_timeout_;
		bool did_connect_server_;



		/**
		 @brief ��M�����f�[�^�Ɋւ�������擾����B
		 @param
		      their_addr: ���M�҂̃A�h���X�����i�[����ϐ��������Ɏw�肵�܂��B
			  data_bytes: ��M�����f�[�^�̃o�C�g�����i�[����ϐ��������Ɏw�肵�܂��B
		 @return
		      true: ����ɏ����擾�����B(�f�[�^�����o�����Ԃł���)
			  false: ���̎擾�Ɏ��s�����B(�f�[�^�����o�����Ԃł͂Ȃ��A�����Ɏw�肵���ϐ��̒l�͖����ł���)
		 */
		bool get_received_info(sockaddr_in & their_addr, int & data_bytes) const;

		void set_addr_for_broadcast();
		static void find_server(void * param);
	};
}