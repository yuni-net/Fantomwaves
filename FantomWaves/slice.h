#pragma once
#define _CRT_SECURE_NO_DEPRECATE

#pragma warning(push)
#pragma warning(disable:4996)

namespace fw
{
	// Do correspond constructor
	// Do not inherit and Do have vstring

	class slice :public vstring
	{
	public:
		slice & operator() (char * str, const char * separate)
		{
			const char * piece = strtok(str, separate);
			this->add(std::string(piece) );
			while( (piece = strtok(NULL, separate) ) != NULL)
			{
				this->add(std::string(piece) );
			}

			return *this;
		}

		slice & operator() (const char * str, const char * separate)
		{
			char * newstr = new char[strlen(str)+1];
			strcpy(newstr, str);
			(*this)(newstr, separate);
			fw_delarr(newstr);

			return *this;
		}

		slice & operator() (const std::string & str, const std::string & separate)
		{
			(*this)(str.c_str(), separate.c_str() );
			return *this;
		}
		slice & operator() (const std::string & str, const char * separate)
		{
			(*this)(str.c_str(), separate);
			return *this;
		}
	};
}

#pragma warning(pop)