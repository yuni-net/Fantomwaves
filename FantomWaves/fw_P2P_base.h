#pragma once

#include "fw_includes.h"
#include "fw_NetSurfer.h"
#include "fw_thread.h"

namespace fw
{

	class Bindata;

	/**
	peer to peer の通信を司るクラスの基本実装です。
	実際に使用する場合は
	P2PクラスもしくはP2P_without_lifelineクラスを使用してください。
	(1)一度もsendを行っていない状態でデータを受け取ることはあり得ません。
	(2)P2Pをインスタンス化した時点で、そのインスタンス専用のソケットが作成されます。
	(3)全く通信していない状態が数十秒以上続くとデータの受信ができなくなる可能性が高いです。
		こちらからデータを送信すれば再度データの受信ができるようになります。
		これはルーターの仕様です。
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
		@brief データを送ります。
		@param
		surfer: 送信先を指定します。
		data: 送信したいデータを指定します。
		@return
		true: 成功です。
		false: 失敗です。
		*/
		virtual bool send(const NetSurfer & surfer, const Bindata & data) const;

		/**
		@brief 見取り出しの受信データがあるかどうか調べます。
		@return
		true: 見取り出しの受信データがあります。
		false: 見取り出しの受信データはありません。
		*/
		bool are_there_any_left_datas() const;

		/**
		@brief 受信データからデータを一つ取り出します。
		@param
		[out]data: 取り出したデータを保存するBindata型変数を指定します。
		[out]surfer: データの送信者情報を保存するNetSurfer型変数を指定します。
		@return
		true: データが取り出されました。
		false: データの取り出しに失敗しました。dataとsurferの内容は無効なものになっています。
		@detail dataに指定するBindata型変数は、事前に容量を確保しておく必要はありません。
		また、データのバイト数分だけきっちり容量が確保された状態でデータが保存されます。
		*/
		bool pop_received_data(Bindata & data, NetSurfer & surfer);

		/**
		@brief このP2Pに割り当てられたポート番号を取得します。
		@return このP2Pに割り当てられたポート番号を返します。
		@detail 一度もsendしていない状態の場合、この関数が返す値は無効な値です。
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