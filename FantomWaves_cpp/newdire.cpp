#include <fw_newdire.h>

namespace fw
{
	// Windows限定。
	// 新規ディレクトリを作成する。
	// 最後の\は不要。
	// @return true...成功　false...失敗
	bool newdire(const std::string & path)
	{
		BOOL result = MakeSureDirectoryPathExists(fw::cnct() << path << "\\");

		if (result != 0) return true;
		if (GetLastError() == ERROR_ALREADY_EXISTS) return true;

		return false;
	}

}