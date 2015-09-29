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

		/**
		 @return
		      the number of my IP addresses.
		 */
		static int get_num_my_address();

		/**
		 @return
		      the my address with text style.
		 */
		static const std::string & get_my_address_text(int address_No);



	private:
		bool did_succeed;
		Array<unsigned long> myaddr_list;
		Array<std::string> myaddr_text_list;

		static NetWork & get_instance();
		NetWork();
		void listup_alotof_myaddr();
		~NetWork();



	};
}