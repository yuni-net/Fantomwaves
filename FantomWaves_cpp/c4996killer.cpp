#include <c4996killer.h>

namespace fw
{
	std::string get_textIP(const IN_ADDR & addr)
	{
		const size_t buffsize = 32;
		char buff[buffsize];
		IN_ADDR copy_addr = addr;
		inet_ntop(AF_INET, &copy_addr, buff, buffsize);
		return std::string(buff);
	}
}