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
		@brief �z�X�g�l�[�����w�肵�ď���������B
		@param �Ⴆ��"example.com"���Ƃ���B
		@detail
			to_string()��to_ccharp()�ɂ����IP�A�h���X�����o���ہA
			���̓s�xDNS�T�[�o�[�𗘗p���ăz�X�g�l�[������IP�A�h���X�ɕϊ����Ēl��Ԃ��B
		*/
		IP(const char * hostname);

		/**
		@brief �z�X�g�l�[�����w�肵�ď���������B
		@param �Ⴆ��"example.com"���Ƃ���B
		*/
		IP(const std::string & hostname);

		/**
		@brief �ʂ�IP�Ɠ���IP�A�h���X�ŏ���������B
		@param �R�s�[������IP�A�h���X���w�肷��B
		*/
		IP(const IP & another);

		/**
		@brief �ʂ�IP����IP�A�h���X���R�s�[����B
		@param �R�s�[������IP�A�h���X���w�肷��B
		*/
		IP & operator=(const IP & another);

		/**
		@brief �ʂ�IP�Ɠ���IP�A�h���X��ݒ肷��B
		@param �R�s�[������IP�A�h���X���w�肷��B
		*/
		void set(const IP & another);

		/**
		@brief IP�A�h���X��ݒ肷��B
		@param �Ⴆ��"192.168.11.22"�Ȃ�set(192, 168, 11, 22)�Ƃ���B
		*/
		void set(const uchar a, const uchar b, const uchar c, const uchar d);

		/**
		@brief IP�A�h���X���A�z�X�g�l�[���Őݒ肷��B
		@detail
			to_string()��to_ccharp()�ɂ����IP�A�h���X�����o���ہA
			���̓s�xDNS�T�[�o�[�𗘗p���ăz�X�g�l�[������IP�A�h���X�ɕϊ����Ēl��Ԃ��B
		*/
		void set_by_hostname(const char * hostname);

		/**
		@brief IP�A�h���X���A�z�X�g�l�[���Őݒ肷��B
		@detail
			to_string()��to_ccharp()�ɂ����IP�A�h���X�����o���ہA
			���̓s�xDNS�T�[�o�[�𗘗p���ăz�X�g�l�[������IP�A�h���X�ɕϊ����Ēl��Ԃ��B
		*/
		void set_by_hostname(const std::string & hostname);

		/**
		@brief IP�A�h���X�𕶎���Ƃ��Ď��o���B
		@return
			IP�A�h���X��������Ƃ��ĕԂ�B
			���������̃P�[�X�̏ꍇ�A"Not Found the Address"�Ƃ��������񂪕Ԃ�B
			(1)���������̏��
			(2)�w�肵���z�X�g�l�[��������
			(3)DNS�T�[�o�[�Ƃ̒ʐM�Ɏ��s
			(4)���̑��Ȃ�炩�̗��R�Ńz�X�g������A�h���X���擾���邱�Ƃ��ł��Ȃ������ꍇ
		@example "192.168.11.22"
		 */
		const std::string to_string() const;









		IP(const sockaddr_in & address);
		void set(const sockaddr_in & address);

		/**
		 @brief inet_addr�֐���p����IP�A�h���X��ULONG�l�ɕϊ�������̒l��Ԃ��B
		 @return
			 inet_addr�֐���p����IP�A�h���X��ULONG�l�ɕϊ�������̒l��Ԃ��B
			 ���������̃P�[�X�̏ꍇ�AINADDR_NONE���Ԃ�B
			 (1)���������̏��
			 (2)�w�肵���z�X�g�l�[��������
			 (3)DNS�T�[�o�[�Ƃ̒ʐM�Ɏ��s
			 (4)���̑��Ȃ�炩�̗��R�Ńz�X�g������A�h���X���擾���邱�Ƃ��ł��Ȃ������ꍇ
		 */
		unsigned long to_inet_addr() const;


	private:
		std::string hostname;
	};
}