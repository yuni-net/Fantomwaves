#define _CRT_SECURE_NO_DEPRECATE

#pragma once

#include "fw_WindowEx.h"
#include "fw_typedef.h"

namespace fw
{

	const uint childnum = 24;

	class ForView
	{
		WindowEx w;
		WindowEx::text children[childnum];
		uint next;

	public:

		ForView(){
			w.init("Information", 800, 480);

			for (uint i = 0; i < childnum; ++i) children[i].create(w, "", 0, 19 * i, 800, 19);
			next = 0;
		}

		void clear(){
			for (uint i = 0; i < childnum; ++i) children[i].sets("");
			next = 0;
		}
		void add(const std::string & str){ if (next < childnum) children[next++].sets(str); }
		void set(const std::string & str, uint index){ if (next < childnum) children[index].sets(str); }

		void del(){ w.del(); }
	};

	ForView & view();

}