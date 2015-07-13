#pragma once

#include "fw_includes.h"
#include "fw_typedef.h"

namespace fw
{
	/***
	@brief �������擾���܂��B
	@detail (min-max)�͈̗̔͂������擾���܂��B
		min��max�Ɏw�肵���l�̑召���t�������ꍇ�A�ǂ�ȋ����ɂȂ�̂��m������������Ȃ��ł��B
	@return ����
	*/
	int stdrandom(int min, int max);

	/***
	@brief �������擾���܂��B
	@detail (min-max)�͈̗̔͂������擾���܂��B
		min��max�Ɏw�肵���l�̑召���t�ł����v�Ȃ悤�ɓ����ŏ������Ă��܂��B
	@return ����
	*/
	int stdrandom_(int min, int max);

	/***
	@brief stdrandom(0, max)�Ɠ����ł��B
	*/
	int stdrandom(int max);

	/***
	@brief �����̃V�[�h��ݒ肵�܂��B
	*/
	uint restdrandom(uint value);

	/***
	@brief �����̃V�[�h��time(NULL)�ɐݒ肵�܂��B
	*/
	uint restdrandom();

}
