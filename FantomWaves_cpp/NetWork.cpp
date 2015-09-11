#include <fw_includes.h>
#include <fw_NetWork.h>

namespace fw
{
	void NetWork::init_ifneed()
	{
		static NetWork network;
	}




	NetWork::NetWork()
	{
		WSADATA wsa;
		WSAStartup(MAKEWORD(2, 2), &wsa);
	}
	NetWork::~NetWork()
	{
		WSACleanup();
	}
}