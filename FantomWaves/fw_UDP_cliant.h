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
		 @brief サーバーへの接続を開始する。
		 @param
		      port: ポート番号を指定する。
			  data: 自分が正規のクライアントであることを証明するデータを指定する。
			  limit_time: サーバーからの応答を待つ制限時間を秒数で指定する。
			  server_response: 送り返されてきたデータがこれと一致すれば、それをサーバーとみなす。
		 @return
		      true: 成功
			  false: 失敗
		 */
		bool connect_server(
			const unsigned short port,
			const Bindata & data,
			const int limit_time,
			const Bindata & server_response);

		/**
		 @return
		      true: 制限時間以内にサーバーが見つからなかった。
			  false: まだ制限時間に達していないか、既にサーバーが見つかっている。
		 */
		bool did_timeout() const;

		/**
		 @return
		      true: サーバーに接続した。
			  false: サーバーに接続していない。
		 */
		bool did_connect_server() const;

		/**
		 @return
		      true: まだ取り出されていないデータがある。
			  false: 全てのデータは既に取り出されている。
		 */
		bool are_there_any_left_datas() const;

		/**
		 @brief 未取り出しの受信データから最も古いものを取り出す。
		 @param 取り出したデータを格納するBindata型変数を指定する。
		 @return
		      true: データを取り出した。
			  false: データを取り出さなかった。(未取り出しデータが無かった)
		 */
		bool pop_received_data(Bindata & buffer);

		/**
		 @brief サーバーにデータを送信する。
		 @param 送信したいデータを指定する。
		 */
		bool send(const Bindata & data) const;

		/**
		 @return サーバーのIPアドレスを返す。
		 */
	//	const IP & get_server_IP() const;

		/**
		 @return サーバーのポート番号を返す。
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
		 @brief 受信したデータに関する情報を取得する。
		 @param
		      their_addr: 送信者のアドレス情報を格納する変数をここに指定します。
			  data_bytes: 受信したデータのバイト数を格納する変数をここに指定します。
		 @return
		      true: 正常に情報を取得した。(データが取り出せる状態である)
			  false: 情報の取得に失敗した。(データを取り出せる状態ではなく、引数に指定した変数の値は無効である)
		 */
		bool get_received_info(sockaddr_in & their_addr, int & data_bytes) const;

		void set_addr_for_broadcast();
		static void find_server(void * param);
	};
}