#pragma once

#include "fw_includes.h"
#include "fw_IP.h"

namespace fw
{
	/**
	 * UDP上での通信者を表すクラス。
	 * IPアドレス・ポート番号等の情報を管理している。
	 */
	class NetSurfer
	{
	public:
		/**
		 @brief 2つの通信者が同一であるかどうかを判定する。
		 @detail ただし、同一かどうかの判断材料は、IPアドレスとポート番号のみ。
		 */
		bool operator==(const NetSurfer & another) const;
		bool operator!=(const NetSurfer & another) const;

		NetSurfer & operator=(const NetSurfer & another);




		NetSurfer();
		NetSurfer(const IP & ip, const unsigned short port);

		void set_ip(const IP & ip);
		void set_port(const unsigned short port);
		void set(const IP & ip, const unsigned short port);

		IP get_ip() const;
		unsigned short get_port() const;





		void set_address(const sockaddr_in & address);
		const sockaddr_in & get_address() const;
		const sockaddr * get_address_pointer() const;
		int get_address_bytes() const;

	private:
		IP ip;
		sockaddr_in addr;


		void construct();
	};
}