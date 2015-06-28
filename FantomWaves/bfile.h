#define _CRT_SECURE_NO_DEPRECATE
#pragma once

#include "includes.h"
#include "typedef.h"
#include "vtypedef.h"
#include "cast.h"
#include "filesize.h"
#include "path.h"

#pragma warning(push)
#pragma warning(disable:4996)

namespace fw
{

	bool delfile(const char * filepath);
	bool delfile(const std::string & filepath);

	/*
	 * バイナリファイルの読み書きを司る
	 *
	 * 明示的にファイルをオープンしなくても、必要になったら暗黙的にファイルがオープンされる
	 * open_to_read, open_to_writeを使って明示的にオープンすることも可能
	 * 
	 * 明示的にファイルをクローズしなくても、デストラクタによって暗黙的にファイルがクローズされる
	 * closeを使って明示的にクローズすることも可能
	 *
	 */
	class bfile
	{
	public:
		bfile();
		bfile(const char * path_);			// インスタンス化時にファイルパスを指定することができる。
		bfile(const std::string & path_);	// インスタンス化時にファイルパスを指定することができる。

		// path ********************************************************************************
		/*
		 * インスタンス化後もファイルパスを指定したり変更したりできるが変更する場合は注意が必要
		 * path関数を呼んだ時点で、現在開かれているファイルはクローズされる
		 * 読み出し位置も先頭に戻る
		 *
		 */

		bfile & path(const char * path_);
		bfile & path(const std::string & path_);
		// *************************************************************************************

		// (あらかじめ読み込んでおいた)ファイルの内容を、指定された変数にコピーし、そのバイト数分読み出し位置を進める
		template<typename T>
		bfile & operator>> (T & req)
		{
			divide(req);
			return *this;
		}

		// 現在の読み出し位置が、文字列配列(ヌルで終わる)の先頭アドレスだと仮定し、
		// そのアドレスを返して文字列の次のデータまで読み出し位置をずらす
		const char * as_string();

		const char * head();
		uint byte() const;
		bfile & clear();	// ファイルの内容を空にする

		// ファイルに書き込む
		template<typename T>
		const bfile & operator<< (const T & req) const
		{
			write(req);
			return *this;
		}

		bfile & move(int distance);		// 指定したバイト数分、読み出し位置をずらす
		bfile & position(uint point);	// 読み出し位置(バイト単位)を直接指定する
		uint position() const;			// 現在の読み出し位置(バイト単位)を取得する

		bfile & open_to_read();		// 読み込み用として明示的にファイルを開く
		bfile & open_to_write();	// 書き込み用として明示的にファイルを開く
		void close();				// 明示的にファイルを閉じる

		// divide ***********************************************************************
		/*
		 * (あらかじめ読み込んでおいた)ファイルの内容を、
		 * 指定された変数にコピーし、
		 * そのバイト数分読み出し位置を進める
		 *
		 */

		bfile & divide(void * req, uint size);
		bfile & divide(std::string & req);

		template<typename T>
		bfile & divide(fw::vector<T> & req)
		{
			req.zerosize();
			uint byte(0);
			*this >> byte;
			req.requre(byte);
			for (uint i = 0; i < byte; ++i) *this >> req.next();
			return *this;
		}

		template<typename T>
		bfile & divide(T & req)
		{
			copy(req);
			move(sizeof(T));
			return *this;
		}
		// ******************************************************************************

		// copy *************************************************************************
		/*
		* (あらかじめ読み込んでおいた)ファイルの内容を、
		* 指定された変数にコピーする。
		* divideとは違い、読み出し位置は変化しない
		*
		*/


		bfile & copy(void * req, uint size);
		bfile & copy(std::string & req);

		template<typename T>
		bfile & copy(fw::vector<T> & req)
		{
			req.zerosize();
			uint byte(0);
			*this >> byte;
			req.requre(byte);
			for (uint i = 0; i < byte; ++i) *this >> req.next();
			move(-(sizeof(uint) + sizeof(T)*byte));
			return *this;
		}

		template<typename T>
		bfile & copy(T & req)
		{
			open_if_need(readingmode);
			req = *reinterpret_cast<const T *>(imutable_content().address(position()));
			return *this;
		}

		// ******************************************************************************

		// write ************************************************************************

		const bfile & write(const void * req, uint size) const;

		template<typename T>
		const bfile & write(const fw::vector<T> & req) const
		{
			*this << req.size();
			for (uint i = 0; i < req.size(); ++i) *this << req[i];
			return *this;
		}

		const bfile & write(const std::string & req) const;

		template<typename T>
		const bfile & write(const T & req) const
		{
			write(&req, sizeof(T));
			return *this;
		}

		// ******************************************************************************

		bool finished() const;



		~bfile();
	private:
		enum
		{
			readingmode,
			writingmode,
			addingmode
		};

		mutable vuchar content_;
		uint position_;
		std::string path_;
		mutable FILE * fp;

		void construct();
		vuchar & mutable_content();
		const vuchar & imutable_content() const;
		void open_if_need(uint mode) const;
		void open(uint mode) const;
		FILE * get_fp() const;
	};







#if 0
	// Remember to correspond to DX-archiver ".dxa"
	// Remember to write the class AccesserTo_bfile

	class bfile
	{
	private:
		class ErrorMode
		{
		private:
			enum Mode
			{
				NoneMode,
				UndefinedPathMode,
				NoExistMode,
				UnableOpenMode,
				CalledNeitherOpenNorReadMode
			}
			mode;

		public:
			void None(){ mode = NoneMode; }
			bool ifNone() const { return mode == NoneMode; }

			void UndefinedPath(){ mode = UndefinedPathMode; }
			bool ifUndefinedPath() const { return mode == UndefinedPathMode; }

			void NoExist(){ mode = NoExistMode; }
			bool ifNoExist() const { return mode == NoExistMode; }

			void UnableOpen(){ mode = UnableOpenMode; }
			bool ifUnableOpen() const { return mode == UnableOpenMode; }

			void CalledNeitherOpenNorRead(){ mode = CalledNeitherOpenNorReadMode; }
			bool ifCalledNeitherOpenNorRead() const { return mode == CalledNeitherOpenNorReadMode; }
		};
	public:
		ErrorMode errormode;

	private:
		std::string Path;
	public:
		const std::string & path() const { return Path; }
		bfile & path(const char * filepath)
		{
			Path = filepath;
			return *this;
		}
		bfile & path(const std::string & filepath)
		{
			path(filepath.c_str());
			return *this;
		}

	private:
		bool Create;
	public:
		bool create() const { return Create; }
		bfile & create(bool create)
		{
			Create = create;
			return *this;
		}

	private:
		// Finaly this is called after when any "open" or any "divide" is called.
		FILE * open(bool rmode)
		{
			std::string mode("rb");
			if (rmode == false) mode = "ab";

			if (Path == "")
			{
				errormode.UndefinedPath();
				return NULL;
			}
			if (iffile(Path) == false)
			{
				if (Create)
				{
					FILE * fp = fopen(Path.c_str(), "wb");
					if (fp != NULL) fclose(fp);
				}
				else
				{
					errormode.NoExist();
					return NULL;
				}
			}

			FILE * fp = fopen(Path.c_str(), mode.c_str());
			if (fp == NULL)
			{
				errormode.UnableOpen();
				return NULL;
			}

			errormode.None();

			return fp;
		}

	private:
		void Init(bool Create)
		{
			beg = 0;
			wfp = NULL;
			errormode.CalledNeitherOpenNorRead();
			create(Create);
		}
	public:
		bfile(){ Init(false); }
		bfile(bool Create){ Init(Create); }
		bfile(const char * Path, bool Create = false)
		{
			path(Path);
			Init(Create);
		}
		bfile(const std::string & Path, bool Create = false)
		{
			path(Path);
			Init(Create);
		}

	private:
		vuchar Content;
		uint beg;
	public:
		bfile & read()
		{
			FILE * fp = open(true);
			if (fp == NULL)
			{
				beg = -1;
				return *this;
			}

			fseek(fp, 0, SEEK_END);
			uint byte = ftell(fp);
			fseek(fp, 0, SEEK_SET);
			Content.setsize(byte);
			fread(Content.head(), byte, 1, fp);
			fclose(fp);
			beg = 0;

			return *this;
		}
	private:
		FILE * wfp;
	public:
		bfile & open()
		{
			wfp = open(false);
			return *this;
		}

	public:
		bool wfell() const { return wfp == NULL; }
		bool rfell() const { return beg == -1; }

	public:
		bfile & clear(){
			if (wfp != NULL) fclose(wfp);
			FILE * fp = fopen(Path.c_str(), "wb");
			if (fp != NULL) fclose(fp);
			open();
			return *this;
		}
		const bfile & clear() const
		{
			bfile & ins = unconst_cast<bfile>(*this);
			ins.clear();
			return *this;
		}

	public:
		// Finaly this is called after when any "write" is called.
		const bfile & write(const void * req, uint size) const
		{
			if (wfp != NULL) fwrite(req, size, 1, wfp);
			return *this;
		}
		bfile write(const void * req, uint size)
		{
			const bfile & ci = *this;
			ci.write(req, size);
			return *this;
		}

		template<typename T>
		const bfile & write(const fw::vector<T> & req) const
		{
			*this << req.size();
			for (uint i = 0; i < req.size(); ++i) *this << req[i];
			return *this;
		}
		template<typename T>
		bfile & write(const fw::vector<T> & req)
		{
			const bfile & ci = *this;
			ci.write(req);
			return *this;
		}

		const bfile & write(const std::string & req) const
		{
			if (req.empty() == false) write(req.c_str(), req.length() + 1);
			return *this;
		}
		bfile & write(const std::string & req)
		{
			const bfile & ci = *this;
			ci.write(req);
			return *this;
		}

		template<typename T>
		const bfile & write(const T & req) const
		{
			write(&req, sizeof(T));
			return *this;
		}
		template<typename T>
		bfile & write(const T & req)
		{
			const bfile & ci = *this;
			ci.write(req);
			return *this;
		}

		template<typename T>
		const bfile operator<< (const T & req) const
		{
			write(req);
			return *this;
		}
		template<typename T>
		bfile & operator<< (const T & req)
		{
			write(req);
			return *this;
		}

	public:
		bfile & close()
		{
			if (wfp != NULL) fclose(wfp);
			wfp = NULL;
			return *this;
		}

	public:
		// Finaly this is called after when any "divide" is called.
		bfile & divide(void * req, uint size)
		{
			if (rfell()) return *this;
			if (ImutableContent().size() == 0) return *this;
			memcpy(req, ImutableContent().address(beg), size);
			beg += size;
			return *this;
		}
		template<typename T>
		bfile & divide(fw::vector<T> & req)
		{
			req.zerosize();
			uint byte(0);
			*this >> byte;
			req.requre(byte);
			for (uint i = 0; i < byte; ++i) *this >> req.next();
			return *this;
		}
		bfile & divide(std::string & req)
		{
			if (rfell()) return *this;
			if (ImutableContent().size() == 0) return *this;
			req = pointer_cast<const char *>(ImutableContent().address(beg));
			beg += req.length() + 1;
			return *this;
		}
		template<typename T>
		bfile & divide(T & req)
		{
			if (rfell()) return *this;
			if (ImutableContent().size() == 0) return *this;
			req = *reinterpret_cast<const T *>(ImutableContent().address(beg));
			beg += sizeof(T);
			return *this;
		}

		template<typename T>
		T put()
		{
			T t;
			divide(t);
			return t;
		}
		template<typename T>
		const T & put_ref()
		{
			const T * p = fw::pointer_cast<const T *>(content().address(beg));
			beg += sizeof(T) / sizeof(uchar);
			return *p;
		}

	public:
		const vuchar & content() const { return Content; }
		vuchar & MutableContent(){ return Content; }
		const vuchar & ImutableContent() const { return Content; }
		uint now() const { return beg; }
		uint filesize() const { return content().size(); }
		bool ifend() const {
			if (now() >= byte()) return true;
			return false;
		}

	public:
		bfile & move(int distance)
		{
			beg += distance;
			return *this;
		}
		bfile & illusion(uint point)
		{
			beg = point;
			return *this;
		}

	public:
		~bfile(){ close(); }

	};

#endif



}

#pragma warning(pop)