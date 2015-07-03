#include <fw_newdire.h>

namespace fw
{
	// Windows����B
	// �V�K�f�B���N�g�����쐬����B
	// �Ō��\�͕s�v�B
	// @return true...�����@false...���s
	bool newdire(const std::string & path)
	{
		BOOL result = MakeSureDirectoryPathExists(fw::cnct() << path << "\\");

		if (result != 0) return true;
		if (GetLastError() == ERROR_ALREADY_EXISTS) return true;

		return false;
	}

}