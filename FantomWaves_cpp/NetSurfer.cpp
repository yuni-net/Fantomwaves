#include <fw_NetSurfer.h>
#include <fw_zeromemory.h>
#include <fw_cast.h>

namespace fw
{
	bool NetSurfer::operator==(const NetSurfer & another) const
	{
		if (addr.sin_addr.S_un.S_addr != another.addr.sin_addr.S_un.S_addr)
		{
			return false;
		}
		if (addr.sin_port != another.addr.sin_port)
		{
			return false;
		}
		return true;
	}

	bool NetSurfer::operator!=(const NetSurfer & another) const
	{
		return !(*this == another);
	}


	NetSurfer & NetSurfer::operator=(const NetSurfer & another)
	{
		addr = another.addr;
		return *this;
	}




	NetSurfer::NetSurfer()
	{
		construct();
	}
	NetSurfer::NetSurfer(const IP & ip, const unsigned short port)
	{
		construct();
		set_ip(ip);
		set_port(port);
	}

	void NetSurfer::set_ip(const IP & ip)
	{
		this->ip = ip;
		addr.sin_addr.S_un.S_addr = ip.to_inet_addr();
	}
	void NetSurfer::set_port(const unsigned short port)
	{
		addr.sin_port = htons(port);
	}
	void NetSurfer::set(const IP & ip, const unsigned short port)
	{
		set_ip(ip);
		set_port(port);
	}

	IP NetSurfer::get_ip() const
	{
		return IP(addr);
	}
	unsigned short NetSurfer::get_port() const
	{
		return ntohs(addr.sin_port);
	}





	void NetSurfer::set_address(const sockaddr_in & address)
	{
		ip.set(address);
		addr = address;
	}

	const sockaddr_in & NetSurfer::get_address() const
	{
		return addr;
	}
	const sockaddr * NetSurfer::get_address_pointer() const
	{
		return pointer_cast<const sockaddr *>(&get_address());
	}
	int NetSurfer::get_address_bytes() const
	{
		return sizeof(sockaddr_in);
	}


	void NetSurfer::construct()
	{
		zeromemory(&addr);
		addr.sin_family = AF_INET;
	}

}