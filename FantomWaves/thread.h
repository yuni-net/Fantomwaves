#pragma once

#include "includes.h"

#define fw_thread_ unsigned __stdcall

namespace fw{

	void newthread(void(*function)(void*), void * parameter);

	class thread{
	public:

		thread(){ nullet(); }

		void set(unsigned(__stdcall * function)(void*), void * parameter){
			function_ = function;
			parameter_ = parameter;
		}
		thread(unsigned(__stdcall * function)(void*), void * parameter){
			handle = 0;
			function_ = function;
			parameter_ = parameter;
		}

		void set(unsigned(__stdcall * function)(void*)){ function_ = function; }
		thread(unsigned(__stdcall * function)(void*)){
			nullet();
			function_ = function;
		}

		void set(void * parameter){ parameter_ = parameter; }
		thread(void * parameter){
			nullet();
			parameter_ = parameter;
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
		bool begin(unsigned(__stdcall * function)(void*)){ return begin(function, parameter_); }
		bool begin(void * parameter){ return begin(function_, parameter); }
		bool begin(){ return begin(function_, parameter_); }

		bool working() const {
			if (handle == NULL) return false;
			GetExitCodeThread(handle, &result_);
			if (result_ == STILL_ACTIVE) return true;
			return false;
		}
		bool working(unsigned long & target){
			if (working()) return true;

			target = result_;
			return false;
		}
		bool resting(){ return !working(); }

		unsigned long result() const { return result_; }

		void close(){ if (handle != 0) CloseHandle(handle); }
		~thread(){ close(); }



	private:
		void * handle;
		mutable DWORD result_;
		unsigned(__stdcall * function_)(void*);
		void * parameter_;

		void nullet(){
			handle = NULL;
			function_ = NULL;
			parameter_ = NULL;
		}

	};

}