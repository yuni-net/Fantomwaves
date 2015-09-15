#pragma once

#include "fw_Array.h"

namespace fw
{

	class NetWork
	{
	public:
		static void init_ifneed();
		static bool is_my_address(const unsigned long address);




	private:
		Array<unsigned long> myaddr_list;

		static NetWork & get_instance();
		NetWork();
		void listup_alotof_myaddr();
		~NetWork();



	};
}