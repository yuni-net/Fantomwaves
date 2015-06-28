#include <newshortcut.h>

namespace fw
{
	bool newshortcut(const std::string & lnkpath, const std::string & reqpath)
	{
		bool bResult = false;

		//COMの初期化
		CoInitialize(NULL);

		//IShellLink インターフェースを取得
		IShellLink* psl;
		HRESULT hResult = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, reinterpret_cast<void **>(&psl));
		if (SUCCEEDED(hResult))
		{
			//IPersistFile インターフェースを取得
			IPersistFile* ppf;
			hResult = psl->QueryInterface(IID_IPersistFile, reinterpret_cast<void **>(&ppf));
			if (SUCCEEDED(hResult))
			{
				//リンク元のパスを設定
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
						//ショートカットファイルの保存
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