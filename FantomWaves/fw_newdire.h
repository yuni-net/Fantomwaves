#pragma once
#define _CRT_SECURE_NO_DEPRECATE

#include "fw_includes.h"
#include "fw_cnct.h"

namespace fw
{
	// Windows����B
	// �V�K�f�B���N�g�����쐬����B
	// �Ō��\�͕s�v�B
	// @return true...�����@false...���s
	bool newdire(const std::string & path);

}