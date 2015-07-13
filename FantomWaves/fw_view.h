#define _CRT_SECURE_NO_DEPRECATE

#pragma once

#include "fw_WindowEx.h"
#include "fw_typedef.h"

namespace fw
{

	const uint childnum = 24;

	/***
	�ʃE�B���h�E�ɕ���������񂩕\�����邽�߂̃N���X�ł��B
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
		@brief �\�����e��S�ăN���A���܂��B
		*/
		void clear(){
			for (uint i = 0; i < childnum; ++i) children[i].sets("");
			next = 0;
		}

		/***
		@brief ��i���ɁA�������ǉ����܂��B
		*/
		void add(const std::string & str){ if (next < childnum) children[next++].sets(str); }
		
		/***
		index�Ԗڂ̒i�̕������ύX���܂��B
		*/
		void set(const std::string & str, uint index){ if (next < childnum) children[index].sets(str); }

		/***
		�������\������E�B���h�E�������܂��B
		*/
		void del(){ w.del(); }
	};

	/***
	ForView�N���X�̗B��̃C���X�^���X��Ԃ��܂��B
	*/
	ForView & view();

}