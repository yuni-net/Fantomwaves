#include <stdio.h>
#include <stdlib.h>
#include <Wav.h>
#include <cast.h>
#include <includes.h>

#pragma warning(push)
#pragma warning(disable:4996)

namespace fw
{

	bool Wav::load(FILE * fp)
	{
		typedef struct
		{
			char a;
			char b;
			char c;
			char d;

		} Chunk;


		if (check_format(fp) == false)
		{
			return false;
		}

		while (true)
		{
			Chunk c;

			if (fread(&c, 4, 1, fp) == 0) return false;

			if (c.a == 'f' && c.b == 'm' && c.c == 't' && c.d == ' ')
			{
				if (fmt_chunk(fp) == false) return false;
				continue;
			}

			if (c.a == 'd' && c.b == 'a' && c.c == 't' && c.d == 'a')
			{
				if (data_chunk(fp) == false) return false;
				return true;
			}

			if (unsupported_chunk(fp) == false)
			{
				return false;
			}
		}

		return false;
	}

	bool Wav::load(const char * path)
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
	bool Wav::check_format(FILE * fp)
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

		} Format;


		Format f;

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
	bool Wav::fmt_chunk(FILE * fp)
	{
		if (fseek(fp, 4, SEEK_CUR) != 0) return false;	// ChunkSize. but Untrustworthy
		if (fread(&pwf, sizeof(unsigned short) * 4 + sizeof(unsigned int) * 2, 1, fp) == 0) return false;

		channels_ = pwf.channels;
		if (pwf.format_tag == 1)	// This format is PCM
		{
			if (pwf.bits_per_sample != 8 && pwf.bits_per_sample != 16)
			{
				return false;
			}

			short work;
			if (fread(&work, 2, 1, fp) == 0) return false;	// maybe there are zero (extended Chunk size)
			if (work == 0)
			{
				// ignore this extended Chunk size
			}
			else
			{
				if (fseek(fp, -2, SEEK_CUR) != 0) return false;	// cancel the last fread
			}
		}
		else
		{
			short exchsize;
			if (fread(&exchsize, 2, 1, fp) == 0) return false;	// extended Chunk size
			if (fseek(fp, exchsize, SEEK_CUR) != 0) return false;	// this time I don't support extended Chunk.
		}
		bit_ = pwf.bits_per_sample;
		myHz = pwf.samples_per_sec;

		return true;
	}

	// return 
	//	false ... failure
	//	true  ... success
	bool Wav::unsupported_chunk(FILE * fp)	// this time I ignore it.
	{
		long size = 0;

		if (fread(&size, 4, 1, fp) == 0) return false;
		if (fseek(fp, size, SEEK_CUR) != 0) return false;

		return true;
	}

	// return 
	//	false ... failure
	//	true  ... success
	bool Wav::data_chunk(FILE * fp)
	{
		unsigned long quotient;
		unsigned long surplus;
		unsigned long minsize = 8192;

		if (fread(&(size_), 4, 1, fp) == 0) return false;
		data_ = malloc(size());
		if (data() == NULL) return false;

		quotient = size() / minsize;
		surplus = size() % minsize;
		for (unsigned long i = 0; i < quotient; ++i)
		{
			if (fread(fw::pointer_cast<char *>(data_) +minsize*i, 1, minsize, fp) == 0)
			{
				free(data_);
				return false;
			}
		}
		if (surplus != 0)
		{
			if (fread(fw::pointer_cast<char *>(data_) +quotient*minsize, 1, surplus, fp) == 0)
			{
				free(data_);
				return false;
			}
		}

		return true;
	}


}

#pragma warning(pop)
