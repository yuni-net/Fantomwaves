#pragma once

#include "fw_includes.h"
#include "fw_IP.h"

namespace fw
{
	/**
	 * UDP��ł̒ʐM�҂�\���N���X�B
	 * IP�A�h���X�E�|�[�g�ԍ����̏����Ǘ����Ă���B
	 */
	class NetSurfer
	{
	public:
		/**
		 @brief 2�̒ʐM�҂�����ł��邩�ǂ����𔻒肷��B
		 @detail �������A���ꂩ�ǂ����̔��f�ޗ��́AIP�A�h���X�ƃ|�[�g�ԍ��̂݁B
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