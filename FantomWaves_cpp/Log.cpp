#include <string.h>
#include <fw_Log.h>

namespace fw
{

	void Log::write(const char * text)
	{
#ifdef _DEBUG
		get_instance().ofs << text;
#endif
	}




	Log & Log::get_instance()
	{
		static Log log;
		return log;
	}

	Log::Log()
	{
#ifdef _DEBUG
		ofs.open("data/log.txt", std::ios::out | std::ios::trunc);
#endif
	}

}