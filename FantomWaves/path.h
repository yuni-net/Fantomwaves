#pragma once
#define _CRT_SECURE_NO_DEPRECATE

#include "cnct.h"
#include "includes.h"
#include "typedef.h"
#include "vtypedef.h"

namespace fw
{




	bool iffile(const std::string & path);
	bool iffile(const vstring & path);
	bool ifdire(const std::string & path);
	bool ifdire(const vstring & path);
	std::string root(const std::string & path);	// C:/root/text.txt -> C:/root/
	vstring root(const vstring & path);
	std::string rootdire(const std::string & path);	// C:/rootdire/text.txt -> C:/rootdire
	vstring rootdire(const vstring & path);
	std::string extend(const std::string & filepath);	// file.txt -> .txt
	vstring extend(const vstring & filepath);
	std::string onlyextend(const std::string & filepath);	// file.txt -> txt
	vstring onlyextend(const vstring & filepath);
	std::string filename(const std::string & path);	// C:/file.txt -> file.txt
	std::string onlyname(const std::string & path);	// C:/file.txt -> file, C:/dire -> dire
	vstring onlyname(const vstring & path);
	vstring onlyfile(const vstring & path);
	vstring onlydire(const vstring & path);
	std::string chextend(const std::string & filepath, const std::string & extend);
	vstring chextend(const vstring & filepath, const std::string & extend);
	bool samextend(const std::string & one, const std::string & ano);
	bool checkextend(const std::string & extend, const std::string & path);



	/*
	deepのときワイルドカードを設定してしまうとフォルダ探索ができなくなってしまう
	*/

	class path
	{
	private:
		class Depth
		{
		public:
			Depth(path & p) :parent(p) {}
			void init(){ deep(); }
			path & shallow()
			{
				mode = Shallow;
				return parent;
			}
			path & deep()
			{
				mode = Deep;
				return parent;
			}

			bool ifshallow() const { return mode == Shallow; }
			bool ifdeep() const { return mode == Deep; }

		private:
			path & parent;
			enum Mode{ Shallow, Deep };
			Mode mode;
		};
		class Attribute
		{
		public:
			Attribute(path & p) :parent(p) {}
			void init(){ all(); }
			path & file()
			{
				mode = File;
				return parent;
			}
			path & dire()
			{
				mode = Dire;
				return parent;
			}
			path & all()
			{
				mode = All;
				return parent;
			}

			bool iffile() const { return mode == File; }
			bool ifdire() const { return mode == Dire; }
			bool ifall() const { return mode == All; }

		private:
			path & parent;
			enum Mode{ File, Dire, All };
			Mode mode;
		};

	public:

		path & init(){
			pTarget = &mytarget;
			pWild = &any;
			pExtens = &none;
			depth().init();
			attribute().init();
			return *this;
		}


#pragma warning(push)
#pragma warning(disable:4355)
		path()
			:
			any("*"), none(""),
			mydepth(*this), myattribute(*this)
		{
			init();
		}

		path & directory(const vstring & direpath){
			DirePath = direpath;
			return init();
		}
		path & directory(const std::string & direpath){
			DirePath = direpath;
			return init();
		}

		path(const vstring & direpath)
			:
			any("*"), none(""),
			mydepth(*this), myattribute(*this)
		{
			directory(direpath);
		}
		path(const std::string & direpath)
			:
			any("*"), none(""),
			mydepth(*this), myattribute(*this)
		{
			directory(direpath);
		}
#pragma warning(pop)

		path & target(vstring & target){
			this->pTarget = &target;
			return *this;
		}
		path & deftarget(){ return this->target(this->mytarget); }
		path & wildcard(const std::string & wild){
			this->pWild = &wild;
			return *this;
		}
		path & extention(const std::string & ext){
			this->pExtens = &ext;
			return *this;
		}
		Depth & depth(){ return mydepth; }
		Attribute & attribute(){ return myattribute; }

		uint exe(){
			for (uint i = 0; i < DirePath.size(); i++){
				dispose(DirePath[i]);
			}

			return pTarget->size();
		}
		vstring & get(){
			exe();
			return *pTarget;
		}
		vstring & got(){ return *pTarget; }

	private:

		vstring DirePath;
		vstring * pTarget;
		const std::string * pWild;
		const std::string * pExtens;
		Depth mydepth;
		Attribute myattribute;
		vstring mytarget;
		const std::string any;
		const std::string none;

		void dispose(const std::string & direpath){
			vstring & target = *(this->pTarget);
			const std::string & wild = *(this->pWild);
			const std::string & extens = *(this->pExtens);

			WIN32_FIND_DATA fData;	//ファイル又はフォルダの情報がここに格納される
			HANDLE fHand;			//検索時のハンドルを格納

			fHand = FindFirstFile(fw::cnct() << direpath << "\\" < wild, &fData);   //検索を行い、ハンドルを取得

			do{
				if (fHand == INVALID_HANDLE_VALUE) continue;
				// found file or folder

				if (fData.cFileName == std::string(".") || fData.cFileName == std::string("..")) continue;
				// It's not "." nor ".."

				std::string foundpath = fw::cnct() << direpath << "\\" <<= fData.cFileName;

				if (fData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)	// it's a folder
				{
					if (!mydepth.ifshallow()) dispose(foundpath);	// recursive processing
					if (myattribute.iffile()) continue;
				}
				else													// it's a file
				{
					if (myattribute.ifdire()) continue;
					if (extens != ""){
						const std::string & thextens(fw::extend(foundpath));
						if (extens.find(thextens, 0) == std::string::npos) continue;	// not found
					}
				}

				target += foundpath;

			} while (FindNextFile(fHand, &fData));

			FindClose(fHand);   //検索に使用したデータを破棄
		}
	};



}