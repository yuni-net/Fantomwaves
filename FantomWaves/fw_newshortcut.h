#pragma once

#include "fw_includes.h"

namespace fw
{
	/***
	@brief [Windows����]�V�����V���[�g�J�b�g���쐬���܂��B
	@param
	    lnkpath: �쐬����V���[�g�J�b�g�̃p�X
		reqpath: �V���[�g�J�b�g��̃p�X
	@return true...�����@false...���s
	*/
	bool newshortcut(const std::string & lnkpath, const std::string & reqpath);

}