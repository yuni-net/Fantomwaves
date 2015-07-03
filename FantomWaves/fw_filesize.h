#pragma once
#define _CRT_SECURE_NO_DEPRECATE

#include "fw_includes.h"
#include "fw_typedef.h"

namespace fw{

	/*
	 * filepathに指定したファイルのサイズ(バイト数)を返します
	 */
	uint filesize(const std::string & filepath);

}