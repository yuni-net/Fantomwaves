#include <iostream>
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


	void Bindata::add(const std::string & text)
	{
		mybuffer.add(text.c_str(), text.length() + 1);
	}

	template<typename T> void Bindata::add(const T & data)
	{
		mybuffer.add(&data, sizeof(T));
	}


	void Bindata::show_cmd() const
	{
		for (uint i = 0; i < mybuffer.size(); ++i)
		{
			std::cout << std::string(1, mybuffer[i]) << "(" << uchar(mybuffer[i]) << ")" << std::endl;
		}
	}


	Bindata::Bindata()
	{
		read_beg = 0;
	}

	Bindata & Bindata::operator>>(std::string & text)
	{
		text = mybuffer.address(read_beg);
		read_beg += text.length() + 1;
		return *this;
	}
	template<typename T> Bindata & Bindata::operator>>(T & data)
	{
		memcpy(&data, mybuffer.address(read_beg), sizeof(T));
		read_beg += sizeof(T);
		return *this;
	}


}