#include <fw_gettimeofday.h>
#include <fw_includes.h>

/**
Some of this implementation is copy of the page:
https://social.msdn.microsoft.com/Forums/ja-JP/430449b3-f6dd-4e18-84de-eebd26a8d668/gettimeofday?forum=vcgeneral
*/

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif

namespace fw
{
	double gettimeofday()
	{
		FILETIME ft;
		unsigned __int64 tmpres = 0;
		static int tzflag;

		GetSystemTimeAsFileTime(&ft);

		tmpres |= ft.dwHighDateTime;
		tmpres <<= 32;
		tmpres |= ft.dwLowDateTime;

		/*converting file time to unix epoch*/
		tmpres -= DELTA_EPOCH_IN_MICROSECS;
		tmpres /= 10;  /*convert into microseconds*/

		return static_cast<double>(tmpres / 1000000UL) +
			static_cast<double>(tmpres % 1000000UL)*0.001*0.001;
	}

}