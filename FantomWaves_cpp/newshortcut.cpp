#include <newshortcut.h>

namespace fw
{
	bool newshortcut(const std::string & lnkpath, const std::string & reqpath)
	{
		bool result = false;

		//COMの初期化
		CoInitialize(NULL);

		//IShellLink インターフェースを取得
		IShellLink* psl;
		HRESULT did_get_link = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, reinterpret_cast<void **>(&psl));
		if (SUCCEEDED(did_get_link))
		{
			//IPersistFile インターフェースを取得
			IPersistFile* ppf;
			HRESULT did_get_file = psl->QueryInterface(IID_IPersistFile, reinterpret_cast<void **>(&ppf));
			if (SUCCEEDED(did_get_file))
			{
				//リンク元のパスを設定
				HRESULT did_set_path = psl->SetPath(reqpath.c_str());
				if (SUCCEEDED(did_set_path))
				{
#ifdef UNICODE
					hResult = ppf->Save(lnkpath.c_str(), TRUE);
					if (SUCCEEDED(hResult))
					{
						result = true;
					}
#else
					WCHAR wszShortcutFile[MAX_PATH];
					if (MultiByteToWideChar(CP_ACP, 0, lnkpath.c_str(), -1, wszShortcutFile, MAX_PATH) > 0)
					{
						//ショートカットファイルの保存
						HRESULT did_save = ppf->Save(wszShortcutFile, TRUE);
						if (SUCCEEDED(did_save))
						{
							result = true;
						}
					}
#endif
				}
				ppf->Release();
			}
			psl->Release();
		}

		CoUninitialize();
		return result;
	}

}