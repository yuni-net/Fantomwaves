#define _CRT_SECURE_NO_DEPRECATE

#pragma once

#include "fw_WindowEx.h"
#include "fw_typedef.h"

namespace fw
{

	const uint childnum = 24;

	/***
	別ウィンドウに文字列を何列か表示するためのクラスです。
	*/
	class ForView
	{
		WindowEx w;
		WindowEx::TextField children[childnum];
		uint next;

	public:

		ForView(){
			w.init("Information", 800, 480);

			for (uint i = 0; i < childnum; ++i) children[i].create(w, "", 0, 19 * i, 800, 19);
			next = 0;
		}

		/***
		@brief 表示内容を全てクリアします。
		*/
		void clear(){
			for (uint i = 0; i < childnum; ++i) children[i].sets("");
			next = 0;
		}

		/***
		@brief 一段下に、文字列を追加します。
		*/
		void add(const std::string & str){ if (next < childnum) children[next++].sets(str); }
		
		/***
		index番目の段の文字列を変更します。
		*/
		void set(const std::string & str, uint index){ if (next < childnum) children[index].sets(str); }

		/***
		文字列を表示するウィンドウを消します。
		*/
		void del(){ w.del(); }
	};

	/***
	ForViewクラスの唯一のインスタンスを返します。
	*/
	ForView & view();

}