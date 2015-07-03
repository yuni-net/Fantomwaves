#include <fw_filesize.h>

namespace fw
{
	/*
	* filepathに指定したファイルのサイズ(バイト数)を返します
	*/
	uint filesize(const std::string & filepath){
		WIN32_FIND_DATA file_data;
		FindClose(FindFirstFile(filepath.c_str(), &file_data));
		return static_cast<uint>(file_data.nFileSizeLow);
	}

}