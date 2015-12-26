#include <fw_includes.h>
#include <fw_IP.h>
#include <fw_cnct.h>
#include <fw_cast.h>

#pragma warning(push)
#pragma warning(disable:4996)

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
	IP::IP(const char * hostname)
	{
		set_by_hostname(hostname);
	}
	IP::IP(const std::string & hostname)
	{
		set_by_hostname(hostname);
	}
	IP::IP(const sockaddr_in & address)
	{
		set(address);
	}


	void IP::set(const uchar a, const uchar b, const uchar c, const uchar d)
	{
		hostname = fw::cnct() << int(a) << "." << int(b) << "." << int(c) << "." <<= int(d);
	}
	void IP::set_by_hostname(const char * hostname)
	{
		this->hostname = hostname;
	}
	void IP::set_by_hostname(const std::string & hostname)
	{
		set_by_hostname(hostname.c_str());
	}

	void IP::set(const sockaddr_in & address)
	{
		hostname = inet_ntoa(address.sin_addr);	// todo C4996
	}



	const std::string IP::to_string() const
	{
		ULONG inet_addr_ = inet_addr(hostname.c_str());
		if (inet_addr_ != INADDR_NONE)
		{
			return hostname;
		}

		std::string IP_string;
		HOSTENT * hostent = gethostbyname(hostname.c_str());
		if (hostent == NULL)
		{
			return std::string("Not Found the Address");
		}

		char * base_addr = hostent->h_addr_list[0];
		const in_addr * inaddr = fw::pointer_cast<const in_addr *>(base_addr);
		return std::string(inet_ntoa(*inaddr));
	}


	unsigned long IP::to_inet_addr() const
	{
		ULONG inet_addr_ = inet_addr(hostname.c_str());
		if (inet_addr_ != INADDR_NONE)
		{
			return inet_addr_;
		}

		std::string IP_string;
		HOSTENT * hostent = gethostbyname(hostname.c_str());
		if (hostent == NULL)
		{
			return inet_addr_;
		}

		char * base_addr = hostent->h_addr_list[0];
		const in_addr * inaddr = fw::pointer_cast<const in_addr *>(base_addr);
		return inaddr->S_un.S_addr;
	}
}

#pragma warning(pop)