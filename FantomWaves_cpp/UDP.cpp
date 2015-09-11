#include <fw_UDP.h>

namespace fw
{
	UDP::UDP(unsigned short port)
	{
		// todo
	}

	void UDP::send(const IP_Address & address, const Bindata & data);
	void UDP::broadcast(const Bindata & data);
}