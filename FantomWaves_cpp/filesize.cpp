#include <filesize.h>

namespace fw
{
	uint filesize(const std::string & filepath){
		WIN32_FIND_DATA fData;
		FindClose(FindFirstFile(filepath.c_str(), &fData));
		return static_cast<uint>(fData.nFileSizeLow);
	}

}