#pragma once

#include "fw_includes.h"

namespace fw
{
	/***
	@brief [Windows限定]新しいショートカットを作成します。
	@param
	    lnkpath: 作成するショートカットのパス
		reqpath: ショートカット先のパス
	@return true...成功　false...失敗
	*/
	bool newshortcut(const std::string & lnkpath, const std::string & reqpath);

}