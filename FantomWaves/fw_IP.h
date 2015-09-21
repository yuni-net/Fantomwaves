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
		@brief IPアドレスを設定する。
		@param 例えば"192.168.11.22"ならset(192, 168, 11, 22)とする。
		*/
		void set(const uchar a, const uchar b, const uchar c, const uchar d);

		/**
		@brief IPアドレスを文字列として取り出す。
		@return IPアドレスが文字列として返る。
		@example "192.168.11.22"
		 */
		const std::string & to_string() const;

		/**
		@brief IPアドレスを文字列として取り出す。
		@return IPアドレスが文字列として返る。
		@example "192.168.11.22"
		*/
		const char * to_ccharp() const;








		IP(const sockaddr_in & address);
		void set(const sockaddr_in & address);

		/**
		 @brief inet_addr関数を用いてIPアドレスをULONG値に変換した後の値を返す。
		 */
		unsigned long to_inet_addr() const;


	private:
		std::string IP_string;
		unsigned long inet_addr_;
	};
}