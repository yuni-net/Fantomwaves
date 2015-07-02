#include <fw_copydire.h>

namespace fw
{
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