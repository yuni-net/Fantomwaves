#pragma once

#include "fw_includes.h"
#include "fw_NetSurfer.h"
#include "fw_thread.h"
#include "fw_P2P_base.h"

namespace fw
{

	class Bindata;

	/**
	 peer to peer �̒ʐM���i��N���X�ł��B
	 (1)��x��send���s���Ă��Ȃ���ԂŃf�[�^���󂯎�邱�Ƃ͂��蓾�܂���B
	 (2)�ŏ���send�̂Ƃ��Ɏw�肵�����M��Ɉ��Ԋu(6�b��)�Ń_�~�[�f�[�^(1byte)�𑗂葱���邱�Ƃɂ���ĒʐM���(UDP�z�[��)���ێ����܂��B
	    ����āA���Ԋu�Ńf�[�^�𑗂葱���Ă����Ȃ����M��ɑ΂��Ă��炩����send���s���Ă���ʏ�̗��p���J�n���邱�Ƃ𐄏����܂��B
	 (3)�_�~�[�f�[�^�̑��M�͕ʃX���b�h�ɂčs���邽�߁A���̃N���X��j������ۂ͒��ӂ��K�v�ł��B
		�܂�disconnect_lifeline()���Ăяo���Ă��������B�ʃX���b�h�ɏI���M���������܂��B
		���ɂ��΂炭���Ԃ�u���A�X���b�h�����S�ɏI�������������v����Ă��炱�̃C���X�^���X��j�����Ă��������B
	 (4)P2P���C���X�^���X���������_�ŁA���̃C���X�^���X��p�̃\�P�b�g���쐬����܂��B
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
	class P2P :public P2P_base
	{
	public:
		/**
		 @Override
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
		�_�~�[�f�[�^�̑��M�͕ʃX���b�h�ɂčs���邽�߁A���̃N���X��j������ۂ͒��ӂ��K�v�ł��B
		�܂�disconnect_lifeline()���Ăяo���Ă��������B�ʃX���b�h�ɏI���M���������܂��B
		���ɂ��΂炭���Ԃ�u���A�X���b�h�����S�ɏI�������������v����Ă��炱�̃C���X�^���X��j�����Ă��������B
		*/
		void disconnect_lifeline();

#if 0
		// �����̊֐��͐e�N���XP2P_base�ɂ���Ċ��ɒ�`����Ă��܂��B

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
#endif








		P2P();
	private:
		// 'lifeline' is for UDP hole.
		mutable NetSurfer lifeline;
		mutable bool did_set_lifeline;
		bool am_I_dying;


		void set_lifeline_ifneed(const NetSurfer & surfer) const;
		static void call_I_still_alive(void * parameter);
	};
}