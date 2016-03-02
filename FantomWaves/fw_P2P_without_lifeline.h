#pragma once

#include "fw_P2P_base.h"

namespace fw
{
	/**
	peer to peer �̒ʐM���i��N���X�ł��B
	(1)��x��send���s���Ă��Ȃ���ԂŃf�[�^���󂯎�邱�Ƃ͂��蓾�܂���B
	(2)P2P���C���X�^���X���������_�ŁA���̃C���X�^���X��p�̃\�P�b�g���쐬����܂��B
	(3)�S���ʐM���Ă��Ȃ���Ԃ����\�b�ȏ㑱���ƃf�[�^�̎�M���ł��Ȃ��Ȃ�\���������ł��B
		�����炩��f�[�^�𑗐M����΍ēx�f�[�^�̎�M���ł���悤�ɂȂ�܂��B
		����̓��[�^�[�̎d�l�ł��B
		���̂悤�ȃ��[�^�[�̎d�l�𗝉����Ă���l�݂̂��̃N���X���g�p���Ă��������B
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
	class P2P_without_lifeline :public P2P_base
	{
		// Nothing
	};
}