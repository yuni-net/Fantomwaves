#pragma once

#include "fw_includes.h"
#include "fw_NetSurfer.h"
#include "fw_thread.h"

namespace fw
{

	class Bindata;

	/**
	peer to peer �̒ʐM���i��N���X�̊�{�����ł��B
	���ۂɎg�p����ꍇ��
	P2P�N���X��������P2P_without_lifeline�N���X���g�p���Ă��������B
	(1)��x��send���s���Ă��Ȃ���ԂŃf�[�^���󂯎�邱�Ƃ͂��蓾�܂���B
	(2)P2P���C���X�^���X���������_�ŁA���̃C���X�^���X��p�̃\�P�b�g���쐬����܂��B
	(3)�S���ʐM���Ă��Ȃ���Ԃ����\�b�ȏ㑱���ƃf�[�^�̎�M���ł��Ȃ��Ȃ�\���������ł��B
		�����炩��f�[�^�𑗐M����΍ēx�f�[�^�̎�M���ł���悤�ɂȂ�܂��B
		����̓��[�^�[�̎d�l�ł��B
	*/
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
		if (p2p.are_ther_any_left_datas() == false)
		{
			continue;
		}

		fw::Bindata received_data;
		fw::NetSurfer sent_user;
		p2p.pop_received_data(received_data, sent_user);
	}
#endif
	class P2P_base
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
		virtual bool send(const NetSurfer & surfer, const Bindata & data) const;

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
		@detail data�Ɏw�肷��Bindata�^�ϐ��́A���O�ɗe�ʂ��m�ۂ��Ă����K�v�͂���܂���B
		�܂��A�f�[�^�̃o�C�g����������������e�ʂ��m�ۂ��ꂽ��ԂŃf�[�^���ۑ�����܂��B
		*/
		bool pop_received_data(Bindata & data, NetSurfer & surfer);

		/**
		@brief ����P2P�Ɋ��蓖�Ă�ꂽ�|�[�g�ԍ����擾���܂��B
		@return ����P2P�Ɋ��蓖�Ă�ꂽ�|�[�g�ԍ���Ԃ��܂��B
		@detail ��x��send���Ă��Ȃ���Ԃ̏ꍇ�A���̊֐����Ԃ��l�͖����Ȓl�ł��B
		*/
		unsigned short get_port() const;



		P2P_base();
		~P2P_base();
	private:
		SOCKET sock;
		sockaddr_in addr;


		int get_received_bytes() const;
	};
}