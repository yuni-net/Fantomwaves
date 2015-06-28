#pragma once

#include "includes.h"

#pragma warning(push)
#pragma warning(disable:4996)

namespace fw
{

	class wav
	{
	public:
		void * data(){ return Data; }
		const void * data() const { return Data; }
		DWORD size() const { return Size; }
		int channels(){ return Channels; }
		int bit(){ return Bit; }
		int Hz(){ return myHz; }

		WORD wFormatTag(){ return pwf.wFormatTag; }
		WORD nChannels(){ return pwf.nChannels; }
		DWORD nSamplesPerSec(){ return pwf.nSamplesPerSec; }
		DWORD nAvgBytesPerSec(){ return pwf.nAvgBytesPerSec; }
		WORD nBlockAlign(){ return pwf.nBlockAlign; }
		WORD wBitsPerSample(){ return pwf.wBitsPerSample; }
		WORD cbSize(){ return 0; }


		bool load(const char * path);
		bool load(const std::string & path){ return load(path.c_str() ); }



	private:
		enum Result
		{
			error,
			finish,
			looking
		};

		typedef struct
		{
			WORD wFormatTag;
			WORD nChannels;
			DWORD nSamplesPerSec;
			DWORD nAvgBytesPerSec;
			WORD nBlockAlign;
			WORD wBitsPerSample;

		} PCMWAVEFORMAT;

		PCMWAVEFORMAT pwf;

		void * Data;
		DWORD Size;
		int Channels;
		int Bit;
		int myHz;

		bool load(FILE * fp);

		// return
		//	bi2::False ... not wave file
		//	bi2::True  ... This is wave file!!
		bool CheckFormat(FILE * fp);

		// return 
		//	bi2::False ... failure
		//	bi2::True  ... success
		bool fmtProc(FILE * fp);

		// return 
		//	bi2::False ... failure
		//	bi2::True  ... success
		bool dataProc(FILE * fp);

		// return 
		//	bi2::False ... failure
		//	bi2::True  ... success
		bool unsupported_chunk(FILE * fp);

	};

}

#pragma warning(pop)
