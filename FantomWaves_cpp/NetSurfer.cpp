#include <fw_NetSurfer.h>

namespace fw
{
	bool NetSurfer::operator==(const NetSurfer & another) const
	{
		return addr.sin_addr.S_un.S_addr == another.addr.sin_addr.S_un.S_addr;
	}

	bool NetSurfer::operator!=(const NetSurfer & another) const
	{
		return !(*this == another);
	}

}