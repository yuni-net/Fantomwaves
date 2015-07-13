#pragma once

#include "fw_includes.h"

#pragma warning(push)
#pragma warning(disable:4996)

namespace fw
{
	/***
	wavファイルを取り扱うクラスです。
	*/
	class Wav
	{
	public:
		/***
		@brief wavファイルを読み込みます。
		@param wavファイルのパスを指定します。
		*/
		bool load(const char * path);
		bool load(const std::string & path){ return load(path.c_str() ); }

		/***
		@brief wavファイルの音楽データ部分を取得します。
		*/
		void * data(){ return data_; }
		const void * data() const { return data_; }

		/***
		@brief 音楽データ部分のサイズ(バイト数)を取得します。
		*/
		DWORD size() const { return size_; }

		/***
		@brief チャンネル数を取得します。
		*/
		int channels(){ return channels_; }

		/***
		@brief ビット数を取得します。
		*/
		int bit(){ return bit_; }

		/***
		@brief Hz数を取得します。
		*/
		int Hz(){ return myHz; }

		WORD format_tag(){ return pwf.format_tag; }
		DWORD samples_per_sec(){ return pwf.samples_per_sec; }
		DWORD avg_bytes_per_sec(){ return pwf.avg_bytes_per_sec; }
		WORD block_align(){ return pwf.block_align; }
		WORD bits_per_sample(){ return pwf.bits_per_sample; }
		WORD pwf_size(){ return 0; }





	private:
		enum Result
		{
			error,
			finish,
			looking
		};

		typedef struct
		{
			WORD format_tag;
			WORD channels;
			DWORD samples_per_sec;
			DWORD avg_bytes_per_sec;
			WORD block_align;
			WORD bits_per_sample;

		} WaveFormatPCM;

		WaveFormatPCM pwf;

		void * data_;
		DWORD size_;
		int channels_;
		int bit_;
		int myHz;

		bool load(FILE * fp);

		// return
		//	bi2::False ... not wave file
		//	bi2::True  ... This is wave file!!
		bool check_format(FILE * fp);

		// return 
		//	bi2::False ... failure
		//	bi2::True  ... success
		bool fmt_chunk(FILE * fp);

		// return 
		//	bi2::False ... failure
		//	bi2::True  ... success
		bool data_chunk(FILE * fp);

		// return 
		//	bi2::False ... failure
		//	bi2::True  ... success
		bool unsupported_chunk(FILE * fp);

	};

}

#pragma warning(pop)
