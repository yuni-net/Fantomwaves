#pragma once

#include "fw_includes.h"
#include <ShellAPI.h>
#include "fw_zeromemory.h"
#include "fw_cnct.h"

namespace fw
{
	/*
	 * Windows限定です。
	 * fromに指定したフォルダの中にあるファイルやフォルダの全てをtoに指定したフォルダの直下にコピーします。
	 * toに指定したフォルダが存在しない場合は新規作成確認メッセージが表示されます。
	 */
	bool copyfolder(const char * from, const char * to);
}