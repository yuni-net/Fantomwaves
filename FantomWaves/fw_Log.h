#pragma once

#include <fstream>

namespace fw
{

	class Log
	{
	public:
		static void write(const char * text);



	private:
		std::ofstream ofs;

		static Log & get_instance();
		Log();
	};

}