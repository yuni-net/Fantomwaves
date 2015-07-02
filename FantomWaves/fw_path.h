#pragma once
#define _CRT_SECURE_NO_DEPRECATE

#include "fw_cnct.h"
#include "fw_includes.h"
#include "fw_typedef.h"
#include "fw_vtypedef.h"

namespace fw
{




	bool iffile(const std::string & Path);
	bool iffile(const vstring & Path);
	bool ifdire(const std::string & Path);
	bool ifdire(const vstring & Path);
	std::string root(const std::string & Path);	// C:/root/text.txt -> C:/root/
	vstring root(const vstring & Path);
	std::string rootdire(const std::string & Path);	// C:/rootdire/text.txt -> C:/rootdire
	vstring rootdire(const vstring & Path);
	std::string extend(const std::string & filepath);	// file.txt -> .txt
	vstring extend(const vstring & filepath);
	std::string onlyextend(const std::string & filepath);	// file.txt -> txt
	vstring onlyextend(const vstring & filepath);
	std::string filename(const std::string & Path);	// C:/file.txt -> file.txt
	std::string onlyname(const std::string & Path);	// C:/file.txt -> file, C:/dire -> dire
	vstring onlyname(const vstring & Path);
	vstring onlyfile(const vstring & Path);
	vstring onlydire(const vstring & Path);
	std::string chextend(const std::string & filepath, const std::string & extend);
	vstring chextend(const vstring & filepath, const std::string & extend);
	bool samextend(const std::string & one, const std::string & ano);
	bool checkextend(const std::string & extend, const std::string & Path);



	/*
	deepのときワイルドカードを設定してしまうとフォルダ探索ができなくなってしまう
	*/

	class Path
	{
	private:
		class Depth
		{
		public:
			Depth(Path & p) :parent(p) {}
			void init(){ deep(); }
			Path & shallow()
			{
				mode = shallow_mode;
				return parent;
			}
			Path & deep()
			{
				mode = deep_mode;
				return parent;
			}

			bool ifshallow() const { return mode == shallow_mode; }
			bool ifdeep() const { return mode == deep_mode; }

		private:
			Path & parent;
			enum Mode{ shallow_mode, deep_mode };
			Mode mode;
		};
		class Attribute
		{
		public:
			Attribute(Path & p) :parent(p) {}
			void init(){ all(); }
			Path & file()
			{
				mode = file_mode;
				return parent;
			}
			Path & dire()
			{
				mode = dire_mode;
				return parent;
			}
			Path & all()
			{
				mode = all_mode;
				return parent;
			}

			bool iffile() const { return mode == file_mode; }
			bool ifdire() const { return mode == dire_mode; }
			bool ifall() const { return mode == all_mode; }

		private:
			Path & parent;
			enum Mode{ file_mode, dire_mode, all_mode };
			Mode mode;
		};

	public:

		Path & init(){
			target_ = &mytarget;
			wild_ = &any;
			extens_ = &none;
			depth().init();
			attribute().init();
			return *this;
		}


#pragma warning(push)
#pragma warning(disable:4355)
		Path()
			:
			any("*"), none(""),
			mydepth(*this), myattribute(*this)
		{
			init();
		}

		Path & directory(const vstring & direpath){
			dire_path_ = direpath;
			return init();
		}
		Path & directory(const std::string & direpath){
			dire_path_ = direpath;
			return init();
		}

		Path(const vstring & direpath)
			:
			any("*"), none(""),
			mydepth(*this), myattribute(*this)
		{
			directory(direpath);
		}
		Path(const std::string & direpath)
			:
			any("*"), none(""),
			mydepth(*this), myattribute(*this)
		{
			directory(direpath);
		}
#pragma warning(pop)

		Path & target(vstring & target){
			this->target_ = &target;
			return *this;
		}
		Path & deftarget(){ return this->target(this->mytarget); }
		Path & wildcard(const std::string & wild){
			this->wild_ = &wild;
			return *this;
		}
		Path & extention(const std::string & ext){
			this->extens_ = &ext;
			return *this;
		}
		Depth & depth(){ return mydepth; }
		Attribute & attribute(){ return myattribute; }

		uint exe(){
			for (uint i = 0; i < dire_path_.size(); i++){
				dispose(dire_path_[i]);
			}

			return target_->size();
		}
		vstring & get(){
			exe();
			return *target_;
		}
		vstring & got(){ return *target_; }

	private:

		vstring dire_path_;
		vstring * target_;
		const std::string * wild_;
		const std::string * extens_;
		Depth mydepth;
		Attribute myattribute;
		vstring mytarget;
		const std::string any;
		const std::string none;

		void dispose(const std::string & direpath){
			vstring & target = *(this->target_);
			const std::string & wild = *(this->wild_);
			const std::string & extens = *(this->extens_);

			WIN32_FIND_DATA file_data;	//ファイル又はフォルダの情報がここに格納される
			HANDLE file_hand;			//検索時のハンドルを格納

			file_hand = FindFirstFile(fw::cnct() << direpath << "\\" < wild, &file_data);   //検索を行い、ハンドルを取得

			do{
				if (file_hand == INVALID_HANDLE_VALUE) continue;
				// found file or folder

				if (file_data.cFileName == std::string(".") || file_data.cFileName == std::string("..")) continue;
				// It's not "." nor ".."

				std::string foundpath = fw::cnct() << direpath << "\\" <<= file_data.cFileName;

				if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)	// it's a folder
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

			} while (FindNextFile(file_hand, &file_data));

			FindClose(file_hand);   //検索に使用したデータを破棄
		}
	};



}