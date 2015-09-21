#pragma once

#include <string>
#include "fw_typedef.h"

namespace fw
{
	/**
	 * IP�A�h���X�����Ǘ�����N���X�B
	 */
	class IP
	{
	public:
		IP();

		/**
		 @brief IP�A�h���X���w�肵�ď���������B
		 @param �Ⴆ��"192.168.11.22"�Ȃ�IP(192, 168, 11, 22)�Ƃ���B
		 */
		IP(const uchar a, const uchar b, const uchar c, const uchar d);

		/**
		@brief IP�A�h���X��ݒ肷��B
		@param �Ⴆ��"192.168.11.22"�Ȃ�set(192, 168, 11, 22)�Ƃ���B
		*/
		void set(const uchar a, const uchar b, const uchar c, const uchar d);

		/**
		@brief IP�A�h���X�𕶎���Ƃ��Ď��o���B
		@return IP�A�h���X��������Ƃ��ĕԂ�B
		@example "192.168.11.22"
		 */
		const std::string & to_string() const;

		/**
		@brief IP�A�h���X�𕶎���Ƃ��Ď��o���B
		@return IP�A�h���X��������Ƃ��ĕԂ�B
		@example "192.168.11.22"
		*/
		const char * to_ccharp() const;








		IP(const sockaddr_in & address);
		void set(const sockaddr_in & address);

		/**
		 @brief inet_addr�֐���p����IP�A�h���X��ULONG�l�ɕϊ�������̒l��Ԃ��B
		 */
		unsigned long to_inet_addr() const;


	private:
		std::string IP_string;
		unsigned long inet_addr_;
	};
}