#pragma once

#include "fw_includes.h"
#include "fw_NetSurfer.h"

namespace fw
{
	class Bindata;

	/**
	 peer to peer の通信を司るクラスです。
	 (1)一度もsendを行っていない状態でデータを受け取ることはあり得ません。
	 (2)最初のsendのときに指定した送信先に一定間隔(6秒毎)でダミーデータ(1byte)を送り続けることによって通信状態(UDPホール)を維持します。
	    よって、一定間隔でデータを送り続けても問題ない送信先に対してあらかじめsendを行ってから通常の利用を開始することを推奨します。
	 (3)P2Pをインスタンス化した時点で、そのインスタンス専用のソケットが作成されます。
	 */
	class P2P
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
		bool send(const NetSurfer & surfer, const Bindata & data) const;

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
		 */
		bool pop_received_data(Bindata & data, NetSurfer & surfer);

		/**
		 @brief このP2Pに割り当てられたポート番号を取得します。
		 @return このP2Pに割り当てられたポート番号を返します。
		 @detail 一度もsendしていない状態の場合、この関数が返す値は無効な値です。
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