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


	/**
	�V�K�X���b�h�̍쐬����Ǘ��A�j���܂ł��ȒP�ɍs���܂��B
	�V�K�X���b�h��Ŏ��s�������֐���
	fw_thread_ your_function(void * parameter) {
		// todo your job
		return 0;
	}
	�Ƃ������ɋL�q����Α��v�ł��B
	*/
	class Thread
	{
	public:

		Thread();

		/***
		@brief ���s�������֐��Ƃ����Ɏw�肷�������ݒ肵�܂��B
		*/
		void set(unsigned(__stdcall * function)(void*), void * parameter);
		Thread(unsigned(__stdcall * function)(void*), void * parameter);

		/***
		@brief ���s�������֐���ݒ肵�܂��B
		*/
		void set(unsigned(__stdcall * function)(void*));
		Thread(unsigned(__stdcall * function)(void*));

		/***
		@brief �����Ɏw�肷��p�����[�^�[��ݒ肵�܂��B
		*/
		void set(void * parameter);
		Thread(void * parameter);

		/***
		@brief �֐���ʃX���b�h�Ŏ��s���܂��B
		@param
			function: ���s�������֐�
			parameter: �֐��̈����ɓn���p�����[�^�[
		@return true...���� false...���s
		*/
		bool begin(unsigned(__stdcall * function)(void*), void * parameter);
		bool begin(unsigned(__stdcall * function)(void*));
		bool begin(void * parameter);
		bool begin();

		/***
		@brief �֐����܂����s�����ǂ������擾���܂��B
		@return true...���s�� false...���s�͊��ɏI�����Ă���
		*/
		bool working() const;

		/***
		@brief �֐����܂����s�����ǂ������擾���܂��B
		@param �X���b�h�̏I���R�[�h���擾����ϐ��������Ɏw�肵�܂��B
		@return true...���s�� false...���s�͊��ɏI�����Ă���
		*/
		bool working(unsigned long & target);
		bool resting();

		/***
		@brief �X���b�h�̏I���R�[�h���擾���܂��B
		*/
		unsigned long result() const;

		/***
		@brief �X���b�h�̃n���h�����������܂��B
		@warning
			�X���b�h�̃n���h����������Ă��X���b�h�͎����ŏI�������肵�܂���B
			�X���b�h������I������悤�Ɏd�����A�X���b�h�����S�ɏI�������������v����Ă���n���h�����������K�v������܂��B
		*/
		void close_handle();
		~Thread();



	private:
		void * handle;
		mutable DWORD result_;
		unsigned(__stdcall * function_)(void*);
		void * parameter_;

		void nullet();

	};

}