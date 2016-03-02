#pragma once

#include "fw_P2P_base.h"

namespace fw
{
	/**
	peer to peer の通信を司るクラスです。
	(1)一度もsendを行っていない状態でデータを受け取ることはあり得ません。
	(2)P2Pをインスタンス化した時点で、そのインスタンス専用のソケットが作成されます。
	(3)全く通信していない状態が数十秒以上続くとデータの受信ができなくなる可能性が高いです。
		こちらからデータを送信すれば再度データの受信ができるようになります。
		これはルーターの仕様です。
		このようなルーターの仕様を理解している人のみこのクラスを使用してください。
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