#pragma once

#include "fw_Array.h"

namespace fw
{
	const unsigned short min_ephemeral_port = 49152;
	const unsigned short max_ephemeral_port = 65535;

	class NetWork
	{
	public:
		/**
		 @return
		      true: succeeded to init.
			  false: failed to init.
		 */
		static bool init_ifneed();

		/**
		 @return
		      true: 'address' is my address.
			  false: 'address' is NOT my address.
		 */
		static bool is_my_address(const unsigned long address);




	private:
		bool did_succeed;
		Array<unsigned long> myaddr_list;

		static NetWork & get_instance();
		NetWork();
		void listup_alotof_myaddr();
		~NetWork();



	};
}