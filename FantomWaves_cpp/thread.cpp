#include <thread.h>

namespace fw
{
	void newthread(void(*function)(void*), void * parameter)
	{
		_beginthread(function, 0, parameter);
	}

}