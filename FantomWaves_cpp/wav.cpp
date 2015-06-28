#include <wav.h>
#include <stdio.h>
#include <stdlib.h>
#include <cast.h>
#include <includes.h>

#pragma warning(push)
#pragma warning(disable:4996)

namespace fw
{

	bool wav::load(FILE * fp)
	{
		typedef struct
		{
			char a;
			char b;
			char c;
			char d;

		} chunk;


		if (CheckFormat(fp) == false)
		{
			return false;
		}

		while (true)
		{
			chunk c;

			if (fread(&c, 4, 1, fp) == 0) return false;

			if (c.a == 'f' && c.b == 'm' && c.c == 't' && c.d == ' ')
			{
				if (fmtProc(fp) == false) return false;
				continue;
			}

			if (c.a == 'd' && c.b == 'a' && c.c == 't' && c.d == 'a')
			{
				if (dataProc(fp) == false) return false;
				return true;
			}

			if (unsupported_chunk(fp) == false)
			{
				return false;
			}
		}

		return false;
	}

	bool wav::load(const char * path)
	{
		FILE * fp = fopen(path, "rb");

		if (fp == NULL)
		{
			return false;
		}

		bool result = load(fp);

		fclose(fp);

		return result;
	}




	// return
	//	false ... not wave file
	//	true  ... This is wave file!!
	bool wav::CheckFormat(FILE * fp)
	{
		typedef struct
		{
			char R;
			char I;
			char F_1;
			char F_2;
			long filesize;
			char W;
			char A;
			char V;
			char E;

		} format;


		format f;

		if (fread(&f, 4 * 3, 1, fp) == 0) return false;
		if (f.R != 'R') return false;
		if (f.I != 'I') return false;
		if (f.F_1 != 'F') return false;
		if (f.F_2 != 'F') return false;
		if (f.W != 'W') return false;
		if (f.A != 'A') return false;
		if (f.V != 'V') return false;
		if (f.E != 'E') return false;

		return true;
	}

	// return 
	//	false ... failure
	//	true  ... success
	bool wav::fmtProc(FILE * fp)
	{
		if (fseek(fp, 4, SEEK_CUR) != 0) return false;	// ChunkSize. but Untrustworthy
		if (fread(&pwf, sizeof(unsigned short) * 4 + sizeof(unsigned int) * 2, 1, fp) == 0) return false;

		Channels = pwf.nChannels;
		if (pwf.wFormatTag == 1)	// This format is PCM
		{
			if (pwf.wBitsPerSample != 8 && pwf.wBitsPerSample != 16)
			{
				return false;
			}

			short work;
			if (fread(&work, 2, 1, fp) == 0) return false;	// maybe there are zero (extended chunk size)
			if (work == 0)
			{
				// ignore this extended chunk size
			}
			else
			{
				if (fseek(fp, -2, SEEK_CUR) != 0) return false;	// cancel the last fread
			}
		}
		else
		{
			short exchsize;
			if (fread(&exchsize, 2, 1, fp) == 0) return false;	// extended chunk size
			if (fseek(fp, exchsize, SEEK_CUR) != 0) return false;	// this time I don't support extended chunk.
		}
		Bit = pwf.wBitsPerSample;
		myHz = pwf.nSamplesPerSec;

		return true;
	}

	// return 
	//	false ... failure
	//	true  ... success
	bool wav::unsupported_chunk(FILE * fp)	// this time I ignore it.
	{
		long size = 0;

		if (fread(&size, 4, 1, fp) == 0) return false;
		if (fseek(fp, size, SEEK_CUR) != 0) return false;

		return true;
	}

	// return 
	//	false ... failure
	//	true  ... success
	bool wav::dataProc(FILE * fp)
	{
		unsigned long quotient;
		unsigned long surplus;
		unsigned long minsize = 8192;

		if (fread(&(Size), 4, 1, fp) == 0) return false;
		Data = malloc(size());
		if (data() == NULL) return false;

		quotient = size() / minsize;
		surplus = size() % minsize;
		for (unsigned long i = 0; i < quotient; ++i)
		{
			if (fread(fw::pointer_cast<char *>(Data)+minsize*i, 1, minsize, fp) == 0)
			{
				free(Data);
				return false;
			}
		}
		if (surplus != 0)
		{
			if (fread(fw::pointer_cast<char *>(Data)+quotient*minsize, 1, surplus, fp) == 0)
			{
				free(Data);
				return false;
			}
		}

		return true;
	}


}

#pragma warning(pop)
