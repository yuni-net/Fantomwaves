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
		 @brief 文字列データを追加する。
		 @detail 最後のヌル文字も含めて追加される。
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