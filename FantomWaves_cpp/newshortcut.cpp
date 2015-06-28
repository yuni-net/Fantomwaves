#include <newshortcut.h>

namespace fw
{
	bool newshortcut(const std::string & lnkpath, const std::string & reqpath)
	{
		bool bResult = false;

		//COM�̏�����
		CoInitialize(NULL);

		//IShellLink �C���^�[�t�F�[�X���擾
		IShellLink* psl;
		HRESULT hResult = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, reinterpret_cast<void **>(&psl));
		if (SUCCEEDED(hResult))
		{
			//IPersistFile �C���^�[�t�F�[�X���擾
			IPersistFile* ppf;
			hResult = psl->QueryInterface(IID_IPersistFile, reinterpret_cast<void **>(&ppf));
			if (SUCCEEDED(hResult))
			{
				//�����N���̃p�X��ݒ�
				hResult = psl->SetPath(reqpath.c_str());
				if (SUCCEEDED(hResult))
				{
#ifdef UNICODE
					hResult = ppf->Save(lnkpath.c_str(), TRUE);
					if (SUCCEEDED(hResult))
					{
						bResult = true;
					}
#else
					WCHAR wszShortcutFile[MAX_PATH];
					if (MultiByteToWideChar(CP_ACP, 0, lnkpath.c_str(), -1, wszShortcutFile, MAX_PATH) > 0)
					{
						//�V���[�g�J�b�g�t�@�C���̕ۑ�
						hResult = ppf->Save(wszShortcutFile, TRUE);
						if (SUCCEEDED(hResult))
						{
							bResult = true;
						}
					}
#endif
				}
				ppf->Release();
			}
			psl->Release();
		}

		CoUninitialize();
		return bResult;
	}

}