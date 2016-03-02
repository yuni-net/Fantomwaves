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


	/**
	新規スレッドの作成から管理、破棄までを簡単に行えます。
	新規スレッド上で実行したい関数は
	fw_thread_ your_function(void * parameter) {
		// todo your job
		return 0;
	}
	という風に記述すれば大丈夫です。
	*/
	class Thread
	{
	public:

		Thread();

		/***
		@brief 実行したい関数とそこに指定する引数を設定します。
		*/
		void set(unsigned(__stdcall * function)(void*), void * parameter);
		Thread(unsigned(__stdcall * function)(void*), void * parameter);

		/***
		@brief 実行したい関数を設定します。
		*/
		void set(unsigned(__stdcall * function)(void*));
		Thread(unsigned(__stdcall * function)(void*));

		/***
		@brief 引数に指定するパラメーターを設定します。
		*/
		void set(void * parameter);
		Thread(void * parameter);

		/***
		@brief 関数を別スレッドで実行します。
		@param
			function: 実行したい関数
			parameter: 関数の引数に渡すパラメーター
		@return true...成功 false...失敗
		*/
		bool begin(unsigned(__stdcall * function)(void*), void * parameter);
		bool begin(unsigned(__stdcall * function)(void*));
		bool begin(void * parameter);
		bool begin();

		/***
		@brief 関数がまだ実行中かどうかを取得します。
		@return true...実行中 false...実行は既に終了している
		*/
		bool working() const;

		/***
		@brief 関数がまだ実行中かどうかを取得します。
		@param スレッドの終了コードを取得する変数をここに指定します。
		@return true...実行中 false...実行は既に終了している
		*/
		bool working(unsigned long & target);
		bool resting();

		/***
		@brief スレッドの終了コードを取得します。
		*/
		unsigned long result() const;

		/***
		@brief スレッドのハンドルを一つ解放します。
		@warning
			スレッドのハンドルを解放してもスレッドは自動で終了したりしません。
			スレッドが自ら終了するように仕向け、スレッドが完全に終了した頃を見計らってからハンドルを解放する必要があります。
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