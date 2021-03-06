#pragma once
#define _CRT_SECURE_NO_DEPRECATE

namespace fw
{
	/***
	ヌル文字で区切られた複数の文字列を分解して個別に保持するクラス。
	*/
	class Nullice :public vstring
	{
	public:
		// *** Use this function ONLY WHEN the end data is '\0' ***
		Nullice & slice_(const char * str, uint byte)	// "byte" means the length of the data
		{
			uint head = 0;
			while(head < byte)
			{
				*this << std::string(&(str[head]) );
				head += this->last().length()+1;
			}

			return *this;
		}

		Nullice & slice(const char * str, uint byte)	// "byte" means the length of the data
		{
			if(byte==0) return *this;
			if(str[byte-1] != 0)
			{
				char * newstr = new char[byte+1];
				memcpy(newstr, str, byte);
				newstr[byte] = '\0';
				slice_(newstr, byte);
				fw_delarr(newstr);
				return *this;
			}

			return slice_(str, byte);
		}

	};

}