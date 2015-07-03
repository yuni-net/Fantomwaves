#include <fw_copydire.h>

namespace fw
{
	/*
	* Windows限定です。
	* fromに指定したフォルダの中にあるファイルやフォルダの全てをtoに指定したフォルダの直下にコピーします。
	* toに指定したフォルダが存在しない場合は新規作成確認メッセージが表示されます。
	*/
	bool copyfolder(const char * from, const char * to)
	{
		SHFILEOPSTRUCT fop;
		fw::zeromemory(&fop);
		fop.wFunc = FO_COPY;
		fop.pFrom = fw::cnct()<<from<"\\*\0";
		fop.pTo = fw::cnct()<<to<"\0";

		return (SHFileOperation(&fop) == 0);	// 0...succeeded
	}
}