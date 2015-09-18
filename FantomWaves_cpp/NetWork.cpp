#include <fw_includes.h>
#include <fw_NetWork.h>
#include <fw_Log.h>

namespace fw
{
	bool NetWork::init_ifneed()
	{
		return get_instance().did_succeed;
	}

	bool NetWork::is_my_address(const unsigned long address)
	{
		for (uint i = 0; i < get_instance().myaddr_list.size(); ++i)
		{
			if (get_instance().myaddr_list[i] == address)
			{
				return true;
			}
		}
		return false;
	}




	NetWork::NetWork()
	{
		WSADATA wsa;
		did_succeed = WSAStartup(MAKEWORD(2, 2), &wsa)==0;
		if (did_succeed)
		{
			Log::write("succeeded to WSAStartup");
		}
		else
		{
			Log::write("failed to WSAStartup");
		}
		listup_alotof_myaddr();
	}

	NetWork & NetWork::get_instance()
	{
		static NetWork network;
		return network;
	}

	void NetWork::listup_alotof_myaddr()
	{
		const int buffersize = 256;
		char buffer[buffersize];
		gethostname(buffer, buffersize);

		HOSTENT * host = gethostbyname(buffer);

		int addr_No = 0;
		while (true)
		{
			char * base_addr = host->h_addr_list[addr_No];
			if (base_addr == nullptr)
			{
				return;
			}

			const in_addr * inaddr = reinterpret_cast<const in_addr *>(base_addr);
			unsigned long myaddr = inaddr->S_un.S_addr;
			myaddr_list.add(myaddr);
			++addr_No;
		}
	}

	NetWork::~NetWork()
	{
		WSACleanup();
	}
}