#pragma once



namespace fw
{
	class IP_Address;
	class Bindata;

	class UDP
	{
	public:
		UDP(unsigned short port);
		void send(const IP_Address & address, const Bindata & data);
		void broadcast(const Bindata & data);
	};
}