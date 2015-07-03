#include <fw_copydire.h>

namespace fw
{
	/*
	* Windows����ł��B
	* from�Ɏw�肵���t�H���_�̒��ɂ���t�@�C����t�H���_�̑S�Ă�to�Ɏw�肵���t�H���_�̒����ɃR�s�[���܂��B
	* to�Ɏw�肵���t�H���_�����݂��Ȃ��ꍇ�͐V�K�쐬�m�F���b�Z�[�W���\������܂��B
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