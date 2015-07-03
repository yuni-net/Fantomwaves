#include <fw_newshortcut.h>

namespace fw
{
	/***
	@brief [Windows����]�V�����V���[�g�J�b�g���쐬���܂��B
	@param
	lnkpath: �쐬����V���[�g�J�b�g�̃p�X
	reqpath: �V���[�g�J�b�g��̃p�X
	@return true...�����@false...���s
	*/
	bool newshortcut(const std::string & lnkpath, const std::string & reqpath)
	{
		bool result = false;

		//COM�̏�����
		CoInitialize(NULL);

		//IShellLink �C���^�[�t�F�[�X���擾
		IShellLink* psl;
		HRESULT did_get_link = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, reinterpret_cast<void **>(&psl));
		if (SUCCEEDED(did_get_link))
		{
			//IPersistFile �C���^�[�t�F�[�X���擾
			IPersistFile* ppf;
			HRESULT did_get_file = psl->QueryInterface(IID_IPersistFile, reinterpret_cast<void **>(&ppf));
			if (SUCCEEDED(did_get_file))
			{
				//�����N���̃p�X��ݒ�
				HRESULT did_set_path = psl->SetPath(reqpath.c_str());
				if (SUCCEEDED(did_set_path))
				{
#ifdef UNICODE
					HRESULT did_save = ppf->Save(lnkpath.c_str(), TRUE);
					if (SUCCEEDED(did_save))
					{
						result = true;
					}
#else
					WCHAR shortcut_file_path[MAX_PATH];
					if (MultiByteToWideChar(CP_ACP, 0, lnkpath.c_str(), -1, shortcut_file_path, MAX_PATH) > 0)
					{
						//�V���[�g�J�b�g�t�@�C���̕ۑ�
						HRESULT did_save = ppf->Save(shortcut_file_path, TRUE);
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