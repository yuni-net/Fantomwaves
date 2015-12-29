#pragma once

#include <string>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <inaddr.h>
#pragma comment(lib, "ws2_32")

namespace fw
{
	std::string get_textIP(const IN_ADDR & addr);
}