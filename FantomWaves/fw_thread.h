#pragma once

#include "fw_includes.h"

#define fw_thread_ unsigned __stdcall

namespace fw{

	/***
	@brief 関数を別スレッドで実行させます。
	@detail 実行させた後、情報を受け取ったり操作したりすることはできません。
	@param
		function: 実行させたい関数を指定します。戻り値void,引数void*です。
		parameter: 関数の引数に渡したいパラメーターを指定します。
	*/
	void newthread(void(*function)(void*), void * parameter);

	class Thread{
	public:

		Thread(){ nullet(); }

		/***
		@brief 実行したい関数とそこに指定する引数を設定します。
		*/
		void set(unsigned(__stdcall * function)(void*), void * parameter){
			function_ = function;
			parameter_ = parameter;
		}
		Thread(unsigned(__stdcall * function)(void*), void * parameter){
			handle = 0;
			function_ = function;
			parameter_ = parameter;
		}

		/***
		@brief 実行したい関数を設定します。
		*/
		void set(unsigned(__stdcall * function)(void*)){ function_ = function; }
		Thread(unsigned(__stdcall * function)(void*)){
			nullet();
			function_ = function;
		}

		/***
		@brief 引数に指定するパラメーターを設定します。
		*/
		void set(void * parameter){ parameter_ = parameter; }
		Thread(void * parameter){
			nullet();
			parameter_ = parameter;
		}

		/***
		@brief 関数を別スレッドで実行します。
		@param
			function: 実行したい関数
			parameter: 関数の引数に渡すパラメーター
		@return true...成功 false...失敗
		*/
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

		/***
		@brief 関数がまだ実行中かどうかを取得します。
		@return true...実行中 false...実行は既に終了している
		*/
		bool working() const {
			if (handle == NULL) return false;
			GetExitCodeThread(handle, &result_);
			if (result_ == STILL_ACTIVE) return true;
			return false;
		}

		/***
		@brief 関数がまだ実行中かどうかを取得します。
		@param スレッドの終了コードを取得する変数をここに指定します。
		@return true...実行中 false...実行は既に終了している
		*/
		bool working(unsigned long & target){
			if (working()) return true;

			target = result_;
			return false;
		}
		bool resting(){ return !working(); }

		/***
		@brief スレッドの終了コードを取得します。
		*/
		unsigned long result() const { return result_; }

		/***
		@brief スレッドを終了させます。
		*/
		void close(){ if (handle != 0) CloseHandle(handle); }
		~Thread(){ close(); }



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