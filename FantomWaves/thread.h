#pragma once

#include "includes.h"

#define fw_thread_ unsigned __stdcall

namespace fw{

	void newthread(void(*function)(void*), void * parameter);

	class thread{
		void * handle;
		mutable DWORD Result;
		unsigned(__stdcall * Function)(void*);
		void * Parameter;

		void nullet(){
			handle = NULL;
			Function = NULL;
			Parameter = NULL;
		}

	public:

		thread(){ nullet(); }

		void set(unsigned(__stdcall * function)(void*), void * parameter){
			Function = function;
			Parameter = parameter;
		}
		thread(unsigned(__stdcall * function)(void*), void * parameter){
			handle = 0;
			Function = function;
			Parameter = parameter;
		}

		void set(unsigned(__stdcall * function)(void*)){ Function = function; }
		thread(unsigned(__stdcall * function)(void*)){
			nullet();
			Function = function;
		}

		void set(void * parameter){ Parameter = parameter; }
		thread(void * parameter){
			nullet();
			Parameter = parameter;
		}

		bool begin(unsigned(__stdcall * function)(void*), void * parameter){
			close();
			if (function == NULL){
#ifdef FW_THREAD_POP_UP_
				fw::popup("呼び出す関数が指定されていないか、もしくは無効です","fw::threadエラー");
#endif
				throw std::invalid_argument("fw::thread_func_error");
			}

			uintptr_t h = _beginthreadex(NULL, 0, function, parameter, 0, NULL);
			handle = reinterpret_cast<void *>(h);
			return handle != NULL;
		}
		bool begin(unsigned(__stdcall * function)(void*)){ return begin(function, Parameter); }
		bool begin(void * parameter){ return begin(Function, parameter); }
		bool begin(){ return begin(Function, Parameter); }

		bool working() const {
			if (handle == NULL) return false;
			GetExitCodeThread(handle, &Result);
			if (Result == STILL_ACTIVE) return true;
			return false;
		}
		bool working(unsigned long & target){
			if (working()) return true;

			target = Result;
			return false;
		}
		bool resting(){ return !working(); }

		unsigned long result() const { return Result; }

		void close(){ if (handle != 0) CloseHandle(handle); }
		~thread(){ close(); }
	};

}