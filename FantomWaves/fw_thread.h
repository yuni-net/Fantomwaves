#pragma once

#include "fw_includes.h"

#define fw_thread_ unsigned __stdcall

namespace fw{

	/***
	@brief �֐���ʃX���b�h�Ŏ��s�����܂��B
	@detail ���s��������A�����󂯎�����葀�삵���肷�邱�Ƃ͂ł��܂���B
	@param
		function: ���s���������֐����w�肵�܂��B�߂�lvoid,����void*�ł��B
		parameter: �֐��̈����ɓn�������p�����[�^�[���w�肵�܂��B
	*/
	void newthread(void(*function)(void*), void * parameter);

	class Thread{
	public:

		Thread(){ nullet(); }

		/***
		@brief ���s�������֐��Ƃ����Ɏw�肷�������ݒ肵�܂��B
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
		@brief ���s�������֐���ݒ肵�܂��B
		*/
		void set(unsigned(__stdcall * function)(void*)){ function_ = function; }
		Thread(unsigned(__stdcall * function)(void*)){
			nullet();
			function_ = function;
		}

		/***
		@brief �����Ɏw�肷��p�����[�^�[��ݒ肵�܂��B
		*/
		void set(void * parameter){ parameter_ = parameter; }
		Thread(void * parameter){
			nullet();
			parameter_ = parameter;
		}

		/***
		@brief �֐���ʃX���b�h�Ŏ��s���܂��B
		@param
			function: ���s�������֐�
			parameter: �֐��̈����ɓn���p�����[�^�[
		@return true...���� false...���s
		*/
		bool begin(unsigned(__stdcall * function)(void*), void * parameter){
			close();
			if (function == NULL){
#ifdef FW_THREAD_POP_UP_
				fw::popup("�Ăяo���֐����w�肳��Ă��Ȃ����A�������͖����ł�","fw::thread�G���[");
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
		@brief �֐����܂����s�����ǂ������擾���܂��B
		@return true...���s�� false...���s�͊��ɏI�����Ă���
		*/
		bool working() const {
			if (handle == NULL) return false;
			GetExitCodeThread(handle, &result_);
			if (result_ == STILL_ACTIVE) return true;
			return false;
		}

		/***
		@brief �֐����܂����s�����ǂ������擾���܂��B
		@param �X���b�h�̏I���R�[�h���擾����ϐ��������Ɏw�肵�܂��B
		@return true...���s�� false...���s�͊��ɏI�����Ă���
		*/
		bool working(unsigned long & target){
			if (working()) return true;

			target = result_;
			return false;
		}
		bool resting(){ return !working(); }

		/***
		@brief �X���b�h�̏I���R�[�h���擾���܂��B
		*/
		unsigned long result() const { return result_; }

		/***
		@brief �X���b�h���I�������܂��B
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