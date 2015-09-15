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





	private:
		Array<char> mybuffer;
	};
}