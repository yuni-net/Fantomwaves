#include <fw_IP.h>
#include <fw_cnct.h>

namespace fw
{
	void IP::set(const uchar a, const uchar b, const uchar c, const uchar d)
	{
		IP_string = fw::cnct() << int(a) << "." << int(b) << "." << int(c) << "." <<= int(d);
	}

	const std::string & IP::to_string() const
	{
		return IP_string;
	}

	const char * IP::to_ccharp() const
	{
		return to_string().c_str();
	}

}