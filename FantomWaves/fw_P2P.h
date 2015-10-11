#pragma once

#include "fw_includes.h"
#include "fw_NetSurfer.h"

namespace fw
{
	class Bindata;

	/**
	 peer to peer �̒ʐM���i��N���X�ł��B
	 (1)��x��send���s���Ă��Ȃ���ԂŃf�[�^���󂯎�邱�Ƃ͂��蓾�܂���B
	 (2)�ŏ���send�̂Ƃ��Ɏw�肵�����M��Ɉ��Ԋu(6�b��)�Ń_�~�[�f�[�^(1byte)�𑗂葱���邱�Ƃɂ���ĒʐM���(UDP�z�[��)���ێ����܂��B
	    ����āA���Ԋu�Ńf�[�^�𑗂葱���Ă����Ȃ����M��ɑ΂��Ă��炩����send���s���Ă���ʏ�̗��p���J�n���邱�Ƃ𐄏����܂��B
	 (3)P2P���C���X�^���X���������_�ŁA���̃C���X�^���X��p�̃\�P�b�g���쐬����܂��B
	 */
	class P2P
	{
	public:
		/**
		 @brief �f�[�^�𑗂�܂��B
		 @param
			surfer: ���M����w�肵�܂��B
			data: ���M�������f�[�^���w�肵�܂��B
		 @return
			true: �����ł��B
			false: ���s�ł��B
		 */
		bool send(const NetSurfer & surfer, const Bindata & data) const;

		/**
		 @brief �����o���̎�M�f�[�^�����邩�ǂ������ׂ܂��B
		 @return
			true: �����o���̎�M�f�[�^������܂��B
			false: �����o���̎�M�f�[�^�͂���܂���B
		 */
		bool are_there_any_left_datas() const;

		/**
		 @brief ��M�f�[�^����f�[�^������o���܂��B
		 @param
			[out]data: ���o�����f�[�^��ۑ�����Bindata�^�ϐ����w�肵�܂��B
			[out]surfer: �f�[�^�̑��M�ҏ���ۑ�����NetSurfer�^�ϐ����w�肵�܂��B
		 @return
			true: �f�[�^�����o����܂����B
			false: �f�[�^�̎��o���Ɏ��s���܂����Bdata��surfer�̓��e�͖����Ȃ��̂ɂȂ��Ă��܂��B
		 */
		bool pop_received_data(Bindata & data, NetSurfer & surfer);

		/**
		 @brief ����P2P�Ɋ��蓖�Ă�ꂽ�|�[�g�ԍ����擾���܂��B
		 @return ����P2P�Ɋ��蓖�Ă�ꂽ�|�[�g�ԍ���Ԃ��܂��B
		 @detail ��x��send���Ă��Ȃ���Ԃ̏ꍇ�A���̊֐����Ԃ��l�͖����Ȓl�ł��B
		 */
		unsigned short get_port() const;


		// example
#if 0
		fw::P2P p2p;
		const IP ip(192, 168, 56, 1);
		const unsigned short port = 6666;
		fw::NetSurfer surfer(ip, port);
		fw::Bindata data;
		data.add(std::string("example"));
		p2p.send(surfer, data);
		while (true)
		{
			if(p2p.are_ther_any_left_datas()==false)
			{
				continue;
			}

			fw::Bindata received_data;
			fw::NetSurfer sent_user;
			p2p.pop_received_data(received_data, sent_user);
		}
#endif


		P2P();
		~P2P();
	private:
		SOCKET sock;
		sockaddr_in addr;
		mutable NetSurfer lifeline;	// lifeline for UDP hole
		mutable bool did_set_lifeline;
		mutable UINT_PTR timer_id;


		int get_received_bytes() const;
		void set_lifeline_ifneed(const NetSurfer & surfer) const;
		static void CALLBACK call_I_still_alive(HWND, UINT, UINT_PTR, DWORD);
	};
}