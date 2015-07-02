#include <fw_newdire.h>

namespace fw
{
	bool newdire(const std::string & path)
	{
		BOOL result = MakeSureDirectoryPathExists(fw::cnct() << path << "\\");

		if (result != 0) return true;
		if (GetLastError() == ERROR_ALREADY_EXISTS) return true;

		return false;
	}

}