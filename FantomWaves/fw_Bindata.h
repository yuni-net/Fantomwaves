#pragma once

#include "fw_typedef.h"
#include "fw_Array.h"

namespace fw
{
	class Bindata
	{
	public:
		void set_size(const uint bytes);
		char * buffer();
		const char * buffer() const;
		uint bytes() const;
		bool operator!=(const Bindata & another) const;

		/**
		 @brief ������f�[�^��ǉ�����B
		 @detail �Ō�̃k���������܂߂Ēǉ������B
		 */
		void add(const std::string & text);
		template<typename T> void add(const T & data);
		void show_cmd() const;

		Bindata & operator>>(std::string & text);
		template<typename T> Bindata & operator>>(T & data);




		Bindata();
	private:
		Array<char> mybuffer;
		unsigned int read_beg;
	};
}