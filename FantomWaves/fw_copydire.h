#pragma once

#include "fw_includes.h"
#include <ShellAPI.h>
#include "fw_zeromemory.h"
#include "fw_cnct.h"

namespace fw
{
	/*
	 * Windows����ł��B
	 * from�Ɏw�肵���t�H���_�̒��ɂ���t�@�C����t�H���_�̑S�Ă�to�Ɏw�肵���t�H���_�̒����ɃR�s�[���܂��B
	 * to�Ɏw�肵���t�H���_�����݂��Ȃ��ꍇ�͐V�K�쐬�m�F���b�Z�[�W���\������܂��B
	 */
	bool copyfolder(const char * from, const char * to);
}