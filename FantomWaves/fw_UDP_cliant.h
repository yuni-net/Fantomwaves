#pragma once

#include <fw_includes.h>
#include <fw_thread.h>
#include <fw_Array.h>

namespace fw
{
	class Bindata;

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
		 */
		void connect_server(
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
		      true: 受信したデータがあり、まだ取り出されていない状態である。
			  false: 受信したデータは無い。
		 */
		bool did_receive() const;

		/**
		 @return まだ取り出されていない受信データの数が返る。
		 */
		unsigned int num_received_datas() const;

		/**
		 @return 未取り出しの受信データから最も古いものを取り出して返す。
		 */
		Bindata pop_received_data();

		/**
		 @brief サーバーにデータを送信する。
		 @param 送信したいデータを指定する。
		 */
		bool send(const Bindata & data) const;

		/**
		 @return サーバーのIPアドレスを返す。
		 */
		const IP & get_server_IP() const;

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
				if (net.did_receive())
				{
					for (fw::uint i = 0; i < net.num_received_messages(); ++i)
					{
						fw::Bindata data = net.received_message();
						process(data);
					}
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
		IP server_IP;
		int limit_time;
		sockaddr_in addr;
		Bindata server_response;
		fw::Thread thread_;
		bool did_timeout_;
		bool did_connect_server_;
		RingQue<Bindata> received_datas;



		void set_addr_for_broadcast();

		/**
		 @return
		     true: succeeded
			 false: failed
		 */
		bool send_data(const Bindata & data);

		static fw_thread_ find_server(void * param);
	};
}