#pragma once

namespace fw
{

	class ExError
	{
	public:

		ExError(){ str = NULL; }

		const char * get(){
			if(str != NULL){ LocalFree(str); str = NULL; }

			FormatMessage(
				FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_FROM_SYSTEM |
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				GetLastError(),
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				fw::pointer_cast<LPSTR>(&str),
				0,
				NULL
			);

			return str;
		}
		const char * show(){ return str; }

		~ExError(){ if(str != NULL){ LocalFree(str); str = NULL; } }


	private:

		char * str;

	};

}