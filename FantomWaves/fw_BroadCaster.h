#pragma once

#include "fw_includes.h"
#include "fw_NetSurfer.h"
#include "fw_thread.h"

namespace fw
{

	class Bindata;

	/**
	broad-cast�ʐM���i��N���X�̊�{�����ł��B
	(1)��x��send���s���Ă��Ȃ���ԂŃf�[�^���󂯎�邱�Ƃ͂��蓾�܂���B
	(2)�C���X�^���X���������_�ŁA���̃C���X�^���X��p�̃\�P�b�g���쐬����܂��B
	*/
	// example
#if 0
	fw::BroadCaster caster;
	fw::Bindata data;
	data.add(std::string("example"));
	caster.send(data);
	while (true)
	{
		if (p2p.are_there_any_left_datas() == false)
		{
			continue;
		}

		fw::Bindata received_data;
		fw::NetSurfer sent_user;
		caster.pop_received_data(received_data, sent_user);
	}
#endif
	class BroadCaster
	{
	public:
		/**
		@brief �f�[�^�𑗂�܂��B
		@param
		data: ���M�������f�[�^���w�肵�܂��B
		@return
		true: �����ł��B
		false: ���s�ł��B
		*/
		virtual bool send(const unsigned short port, const Bindata & data) const;

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



		BroadCaster();
		~BroadCaster();
	private:
		SOCKET sock;
		sockaddr_in addr;
		NetSurfer target;


		int get_received_bytes() const;
	};
}