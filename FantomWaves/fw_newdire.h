#pragma once
#define _CRT_SECURE_NO_DEPRECATE

#include "fw_includes.h"
#include "fw_cnct.h"

namespace fw
{
	// Windows限定。
	// 新規ディレクトリを作成する。
	// 最後の\は不要。
	// @return true...成功　false...失敗
	bool newdire(const std::string & path);

}