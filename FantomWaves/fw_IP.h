#pragma once

#include <string>
#include "fw_typedef.h"

namespace fw
{
	/**
	 * IPアドレス情報を管理するクラス。
	 */
	class IP
	{
	public:
		IP();

		/**
		@brief IPアドレスを指定して初期化する。
		@param 例えば"192.168.11.22"ならIP(192, 168, 11, 22)とする。
		*/
		IP(const uchar a, const uchar b, const uchar c, const uchar d);

		/**
		@brief ホストネームを指定して初期化する。
		@param 例えば"example.com"等とする。
		@detail
			to_string()やto_ccharp()によってIPアドレスを取り出す際、
			その都度DNSサーバーを利用してホストネームからIPアドレスに変換して値を返す。
		*/
		IP(const char * hostname);

		/**
		@brief ホストネームを指定して初期化する。
		@param 例えば"example.com"等とする。
		*/
		IP(const std::string & hostname);

		/**
		@brief 別のIPと同じIPアドレスで初期化する。
		@param コピーしたいIPアドレスを指定する。
		*/
		IP(const IP & another);

		/**
		@brief 別のIPからIPアドレスをコピーする。
		@param コピーしたいIPアドレスを指定する。
		*/
		IP & operator=(const IP & another);

		/**
		@brief 別のIPと同じIPアドレスを設定する。
		@param コピーしたいIPアドレスを指定する。
		*/
		void set(const IP & another);

		/**
		@brief IPアドレスを設定する。
		@param 例えば"192.168.11.22"ならset(192, 168, 11, 22)とする。
		*/
		void set(const uchar a, const uchar b, const uchar c, const uchar d);

		/**
		@brief IPアドレスを、ホストネームで設定する。
		@detail
			to_string()やto_ccharp()によってIPアドレスを取り出す際、
			その都度DNSサーバーを利用してホストネームからIPアドレスに変換して値を返す。
		*/
		void set_by_hostname(const char * hostname);

		/**
		@brief IPアドレスを、ホストネームで設定する。
		@detail
			to_string()やto_ccharp()によってIPアドレスを取り出す際、
			その都度DNSサーバーを利用してホストネームからIPアドレスに変換して値を返す。
		*/
		void set_by_hostname(const std::string & hostname);

		/**
		@brief IPアドレスを文字列として取り出す。
		@return
			IPアドレスが文字列として返る。
			ただし次のケースの場合、"Not Found the Address"という文字列が返る。
			(1)未初期化の状態
			(2)指定したホストネームが無効
			(3)DNSサーバーとの通信に失敗
			(4)その他なんらかの理由でホスト名からアドレスを取得することができなかった場合
		@example "192.168.11.22"
		 */
		const std::string to_string() const;









		IP(const sockaddr_in & address);
		void set(const sockaddr_in & address);

		/**
		 @brief inet_addr関数を用いてIPアドレスをULONG値に変換した後の値を返す。
		 @return
			 inet_addr関数を用いてIPアドレスをULONG値に変換した後の値を返す。
			 ただし次のケースの場合、INADDR_NONEが返る。
			 (1)未初期化の状態
			 (2)指定したホストネームが無効
			 (3)DNSサーバーとの通信に失敗
			 (4)その他なんらかの理由でホスト名からアドレスを取得することができなかった場合
		 */
		unsigned long to_inet_addr() const;


	private:
		std::string hostname;
	};
}