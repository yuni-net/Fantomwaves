#include <fw_thread.h>

namespace fw
{
	void newthread(void(*function)(void*), void * parameter)
	{
		_beginthread(function, 0, parameter);
	}

	Thread::Thread()
	{
		nullet();
	}

	void Thread::set(unsigned(__stdcall * function)(void*), void * parameter)
	{
		function_ = function;
		parameter_ = parameter;
	}

	Thread::Thread(unsigned(__stdcall * function)(void*), void * parameter)
	{
		handle = 0;
		function_ = function;
		parameter_ = parameter;
	}

	void Thread::set(unsigned(__stdcall * function)(void*))
	{
		function_ = function;
	}

	Thread::Thread(unsigned(__stdcall * function)(void*))
	{
		nullet();
		function_ = function;
	}

	void Thread::set(void * parameter)
	{
		parameter_ = parameter; 
	}

	Thread::Thread(void * parameter)
	{
		nullet();
		parameter_ = parameter;
	}

	bool Thread::begin(unsigned(__stdcall * function)(void*), void * parameter)
	{
		close_handle();
		if (function == NULL){
#ifdef FW_THREAD_POP_UP_
			fw::popup("呼び出す関数が指定されていないか、もしくは無効です", "fw::threadエラー");
#endif
			throw std::invalid_argument("fw::thread_func_error");
		}

		uintptr_t h = _beginthreadex(NULL, 0, function, parameter, 0, NULL);
		handle = reinterpret_cast<void *>(h);
		return handle != NULL;
	}

	bool Thread::begin(unsigned(__stdcall * function)(void*))
	{
		return begin(function, parameter_);
	}

	bool Thread::begin(void * parameter)
	{
		return begin(function_, parameter);
	}

	bool Thread::begin()
	{
		return begin(function_, parameter_); 
	}

	bool Thread::working() const
	{
		if (handle == NULL) return false;
		GetExitCodeThread(handle, &result_);
		if (result_ == STILL_ACTIVE) return true;
		return false;
	}

	bool Thread::working(unsigned long & target)
	{
		if (working()) return true;

		target = result_;
		return false;
	}

	bool Thread::resting()
	{
		return !working();
	}

	unsigned long Thread::result() const
	{
		return result_;
	}

	void Thread::close_handle()
	{
		if (handle != 0) CloseHandle(handle); 
	}

	Thread::~Thread()
	{
		close_handle(); 
	}




	void Thread::nullet()
	{
		handle = NULL;
		function_ = NULL;
		parameter_ = NULL;
	}
}