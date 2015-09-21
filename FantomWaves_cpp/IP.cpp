#include <fw_includes.h>
#include <fw_IP.h>
#include <fw_cnct.h>

namespace fw
{
	IP::IP()
	{
		set(0, 0, 0, 0);
	}
	IP::IP(const uchar a, const uchar b, const uchar c, const uchar d)
	{
		set(a, b, c, d);
	}
	IP::IP(const sockaddr_in & address)
	{
		set(address);
	}


	void IP::set(const uchar a, const uchar b, const uchar c, const uchar d)
	{
		IP_string = fw::cnct() << int(a) << "." << int(b) << "." << int(c) << "." <<= int(d);
		inet_addr_ = inet_addr(to_ccharp());
	}
	void IP::set(const sockaddr_in & address)
	{
		inet_addr_ = address.sin_addr.S_un.S_addr;
		IP_string = inet_ntoa(address.sin_addr);
	}



	const std::string & IP::to_string() const
	{
		return IP_string;
	}

	const char * IP::to_ccharp() const
	{
		return to_string().c_str();
	}

	unsigned long IP::to_inet_addr() const
	{
		return inet_addr_;
	}
}