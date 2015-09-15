#pragma once

#include <string>
#include <fw_typedef.h>

namespace fw
{
	class IP
	{
	public:
		void set(const uchar a, const uchar b, const uchar c, const uchar d);
		const std::string & to_string() const;
		const char * to_ccharp() const;



	private:
		std::string IP_string;
	};
}