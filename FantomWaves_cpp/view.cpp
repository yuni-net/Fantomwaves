#include <view.h>

namespace fw
{
	ForView & view()
	{
		static ForView myview;
		return myview;
	}

}