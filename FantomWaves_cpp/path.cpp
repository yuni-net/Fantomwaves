#include <path.h>

namespace fw
{
	bool iffile(const std::string & path)
	{
		WIN32_FIND_DATA FindData;

		HANDLE hFind = FindFirstFile(path.c_str(), &FindData);
		bool inv = (hFind == INVALID_HANDLE_VALUE);
		FindClose(hFind);
		if (inv) return false;
		if (!(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) return true;

		return false;
	}
	bool iffile(const vstring & path)
	{
		for (uint i = 0; i < path.size(); ++i) if (iffile(path[i]) == false) return false;
		return true;
	}

	bool ifdire(const std::string & path){ return PathIsDirectory(path.c_str()) != (BOOL)false; }
	bool ifdire(const vstring & path)
	{
		for (uint i = 0; i < path.size(); ++i) if (ifdire(path[i]) == false) return false;
		return true;
	}

	std::string root(const std::string & path)
	{
		uint index = path.find_last_of("\\");
		if (index == std::string::npos) return "";
		return path.substr(0, index + 1);
	}
	vstring root(const vstring & path)
	{
		vstring send;
		for (uint i = 0; i < path.size(); ++i) send += root(path[i]);
		return send;
	}

	std::string rootdire(const std::string & path)
	{
		uint index = path.find_last_of("\\");
		if (index == std::string::npos) return "";
		return path.substr(0, index);
	}
	vstring rootdire(const vstring & path)
	{
		vstring send;
		for (uint i = 0; i < path.size(); ++i) send += rootdire(path[i]);
		return send;
	}

	std::string extend(const std::string & filepath)
	{
		uint index = filepath.find_last_of('.');
		return filepath.substr(index);
	}
	vstring extend(const vstring & filepath)
	{
		vstring send;
		for (uint i = 0; i < filepath.size(); ++i) send += extend(filepath[i]);
		return send;
	}

	std::string onlyextend(const std::string & filepath){ return extend(filepath).substr(1); }
	vstring inline onlyextend(const vstring & filepath)
	{
		vstring send;
		for (uint i = 0; i < filepath.size(); ++i) send += onlyextend(filepath[i]);
		return send;
	}

	std::string filename(const std::string & path)
	{
		uint index = path.find_last_of("\\");
		if (index == std::string::npos)
		{
			return path;
		}
		return path.substr(index + 1);
	}


	std::string onlyname(const std::string & path)
	{
		if (iffile(path)){
			uint beg = path.find_last_of("\\");
			uint end = path.find_last_of('.');

			return path.substr(beg + 1, end - beg - 1);
		}
		if (ifdire(path)){
			uint last = path.find_last_of("\\");
			return path.substr(last + 1);
		}
		return std::string();
	}
	vstring onlyname(const vstring & path)
	{
		vstring send;
		for (uint i = 0; i < path.size(); ++i) send += onlyname(path[i]);
		return send;
	}

	vstring onlyfile(const vstring & path)
	{
		vstring send;
		for (uint i = 0; i < path.size(); i++) if (iffile(path[i])) send << path[i];
		return send;
	}

	vstring onlydire(const vstring & path)
	{
		vstring send;
		for (uint i = 0; i < path.size(); i++) if (ifdire(path[i])) send << path[i];
		return send;
	}

	std::string chextend(const std::string & filepath, const std::string & extend)
	{
		uint num = filepath.find_last_of('.');
		std::string bef = filepath.substr(0, num);
		return fw::cnct() << bef < extend;
	}
	vstring chextend(const vstring & filepath, const std::string & extend)
	{
		vstring send;
		for (uint i = 0; i < filepath.size(); ++i) send += chextend(filepath[i], extend);
		return send;
	}

	bool samextend(const std::string & one, const std::string & ano)
	{
		const std::string & onextend = one.substr(one.find_last_of('.') + 1);
		const std::string & anoextend = ano.substr(ano.find_last_of('.') + 1);
		return onextend == anoextend;
	}
	bool checkextend(const std::string & extend, const std::string & path)
	{
		return path.substr(path.length() - extend.length()) == extend;
	}

}