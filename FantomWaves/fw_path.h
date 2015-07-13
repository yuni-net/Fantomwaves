#pragma once
#define _CRT_SECURE_NO_DEPRECATE

#include "fw_cnct.h"
#include "fw_includes.h"
#include "fw_typedef.h"
#include "fw_vtypedef.h"

namespace fw
{
	/***
	@brief ファイルが存在するかどうか判定します。
	@param ここに指定したパスが存在し、かつファイルであるかどうか判定します。
	@return true...It's a file. false...It's a NOT file.
	*/
	bool iffile(const std::string & path);
	bool iffile(const vstring & path);

	/***
	@brief ディレクトリが存在するかどうか判定します。
	@param ここに指定したパスが存在し、かつディレクトリであるかどうか判定します。
	@return true...It's a directory. false...It's a NOT directory.
	*/
	bool ifdire(const std::string & path);
	bool ifdire(const vstring & path);

	/***
	@brief ルートパスを得るとき便利です。
	@param ここに指定したファイル・ディレクトリのパスへのルートパスを得ます。
	@detail パスの最後には / が付きます。
	        例1) C:/root/text.txt -> C:/root/
			例2) C:/root/directory -> C:/root/
			\ を使った表記は使えません。
	@return ルートパス
	*/
	std::string root(const std::string & path);
	vstring root(const vstring & path);

	/***
	@brief ルートディレクトリを得るとき便利です。
	@param ここに指定したファイル・ディレクトリのルートディレクトリを得ます。
	@detail パスの最後に / は付きません。
		例1) C:/root/text.txt -> C:/root
		例2) C:/root/directory -> C:/root
		\ を使った表記は使えません。
	@return ルートディレクトリ
	*/
	std::string rootdire(const std::string & path);
	vstring rootdire(const vstring & Path);

	/***
	@brief ファイルの拡張子を得ます。
	@detail ドット付きです。
	        例) file.txt -> .txt
	@param ここに指定したファイルの拡張子を得ます。
	@return 拡張子
	*/
	std::string extend(const std::string & filepath);	// file.txt -> .txt
	vstring extend(const vstring & filepath);

	/***
	@brief ファイルの拡張子を得ます。
	@detail ドットは付きません。
		例) file.txt -> txt
	@param ここに指定したファイルの拡張子を得ます。
	@return 拡張子
	*/
	std::string onlyextend(const std::string & filepath);	// file.txt -> txt
	vstring onlyextend(const vstring & filepath);

	/***
	@brief ファイル名を得ます。
	@detail 拡張子付きです。
	        例) C:/file.txt -> file.txt
	@param ここに指定したファイルの名前を得ます。
	@return ファイル名
	*/
	std::string filename(const std::string & path);

	/***
	@brief ファイル名やディレクトリ名を得ます。
	@detail ファイル名の場合、拡張子は付きません。
		例1) C:/file.txt -> file
		例2) C:/dire -> dire
	@param ここに指定したパスの名前を得ます。
	@return パス
	*/
	std::string onlyname(const std::string & path);
	vstring onlyname(const vstring & path);

	/***
	@brief パスの配列を渡すと、その中でファイルへのパスだけを集めた配列を返します。
	@param パスの配列
	@return ファイルパスの配列
	*/
	vstring onlyfile(const vstring & path);

	/***
	@brief パスの配列を渡すと、その中でディレクトリのパスだけを集めた配列を返します。
	@param パスの配列
	@return ディレクトリパスの配列
	*/
	vstring onlydire(const vstring & path);

	/***
	@brief 拡張子の部分を変更します。
	@param
		filepath: 変更前のファイルパスを指定します。
		extend: 変更後の拡張子を指定します。ドットは付けてはいけません。
	@return 拡張子が変更された後のファイルパス
	*/
	std::string changextend(const std::string & filepath, const std::string & extend);
	vstring changextend(const vstring & filepath, const std::string & extend);

	/***
	@brief 拡張子が同じかどうか判定します。
	@param
		one: 判定したいパスの一つ
		ano: 判定したいパスのもう一つ
	@return true...同じ false...違う
	*/
	bool samextend(const std::string & one, const std::string & ano);

	/***
	@brief 拡張子が特定の物かどうかチェックする。
	@param
		extend: 特定の拡張子
		path: ここに指定したパスの拡張子がextendと同じかどうかをチェックします。
	@return true...同じ false...違う
	*/
	bool checkextend(const std::string & extend, const std::string & path);



	/*
	memo: deepのときワイルドカードを設定してしまうとフォルダ探索ができなくなってしまう
	*/

	/***
	ファイル・ディレクトリの検索を行うためのクラスです。
	メソッドチェーンによって各種設定を決定した後検索を行うというインターフェイスになっています。
	*/
	class Path
	{
	private:
		/***
		探索の深さ(指定したディレクトリ直下だけなのか以下全部なのか)を指定するときに渡す型です。
		*/
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

		/***
		探索するパスの種類(ファイルだけ・ディレクトリだけ・ファイルとディレクトリ)を指定するときに渡す型です。
		*/
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

		/***
		@brief 探索するディレクトリを指定します。
		*/
		Path & directory(const vstring & direpath){
			dire_path_ = direpath;
			return init();
		}
		Path & directory(const std::string & direpath){
			dire_path_ = direpath;
			return init();
		}

		/***
		@brief 探索したいディレクトリを指定します。
		*/
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

		/***
		@brief 探索結果を格納するストリング配列を指定します。
		*/
		Path & target(vstring & target){
			this->target_ = &target;
			return *this;
		}
		Path & deftarget(){ return this->target(this->mytarget); }

		/***
		@brief 探索したいパスを、ワイルドカードを使って指定します。
		@detail extentionと同時に指定することはできません。
		*/
		Path & wildcard(const std::string & wild){
			this->wild_ = &wild;
			return *this;
		}

		/***
		@brief 探索したいパスを、拡張子を使って指定します。
		@detail wildcardと同時に指定することはできません。
		*/
		Path & extention(const std::string & ext){
			this->extens_ = &ext;
			return *this;
		}

		Depth & depth(){ return mydepth; }
		Attribute & attribute(){ return myattribute; }

		/***
		@brief 探索を実行します。
		*/
		uint exe(){
			for (uint i = 0; i < dire_path_.size(); i++){
				dispose(dire_path_[i]);
			}

			return target_->size();
		}

		/***
		@brief 探索を実行し、その結果を返します。
		*/
		vstring & get(){
			exe();
			return *target_;
		}

		/***
		@brief 探索結果を返します。
		*/
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

		/***
		@brief 再帰的に探索を行います。
		*/
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