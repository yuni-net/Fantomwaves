#pragma once

#include "fw_includes.h"

#pragma warning(push)
#pragma warning(disable:4996)

namespace fw
{
	/***
	wav�t�@�C������舵���N���X�ł��B
	*/
	class Wav
	{
	public:
		/***
		@brief wav�t�@�C����ǂݍ��݂܂��B
		@param wav�t�@�C���̃p�X���w�肵�܂��B
		*/
		bool load(const char * path);
		bool load(const std::string & path){ return load(path.c_str() ); }

		/***
		@brief wav�t�@�C���̉��y�f�[�^�������擾���܂��B
		*/
		void * data(){ return data_; }
		const void * data() const { return data_; }

		/***
		@brief ���y�f�[�^�����̃T�C�Y(�o�C�g��)���擾���܂��B
		*/
		DWORD size() const { return size_; }

		/***
		@brief �`�����l�������擾���܂��B
		*/
		int channels(){ return channels_; }

		/***
		@brief �r�b�g�����擾���܂��B
		*/
		int bit(){ return bit_; }

		/***
		@brief Hz�����擾���܂��B
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
