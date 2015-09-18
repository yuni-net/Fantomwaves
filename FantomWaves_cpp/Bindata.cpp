#include <fw_Bindata.h>

namespace fw
{
	void Bindata::set_size(const uint bytes)
	{
		mybuffer.setsize(bytes);
	}

	char * Bindata::buffer()
	{
		return mybuffer.head();
	}

	const char * Bindata::buffer() const
	{
		return mybuffer.head();
	}

	uint Bindata::bytes() const
	{
		return mybuffer.size();
	}

	bool Bindata::operator!=(const Bindata & another) const
	{
		if (bytes() != another.bytes())
		{
			return true;
		}

		if (memcmp(buffer(), another.buffer(), bytes()) == 0)
		{
			return false;
		}

		return true;
	}


}