#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "fw_thread.h"

#pragma warning(disable : 4996)

namespace fw
{

	class Exeexe
	{
	public:

		Exeexe()
		{
			str = NULL;
			timeout_ = INFINITE;
		}

		Exeexe & timeout(const DWORD timeout)
		{
			timeout_ = timeout;
			return *this;
		}

		Exeexe & exepath(const char * path)
		{
			exe_path = fw::cnct() << '\"' << path < '\"';
			return *this;
		}
		Exeexe & exepath(const std::string & path)
		{
			exe_path = fw::cnct() << '\"' << path < '\"';
			return *this;
		}
		Exeexe & _exepath(const char * path)
		{
			exe_path = path;
			return *this;
		}
		Exeexe & _exepath(const std::string & path)
		{
			exe_path = path;
			return *this;
		}

		Exeexe & argus(const char * path)
		{
			argus_ = path;
			return *this;
		}
		Exeexe & argus(const std::string & path)
		{
			argus_ = path;
			return *this;
		}

		void get_message()
		{
			succeeded = false;

			Handles handles;

			SECURITY_ATTRIBUTES	sa;
			sa.nLength = sizeof(sa);
			sa.lpSecurityDescriptor = 0;
			sa.bInheritHandle = true;
			if (!CreatePipe(&(handles.read), &(handles.write), &sa, 0)) return;

			static STARTUPINFO si;
			fw::zeromemory(&si);
			si.cb = sizeof(si);
			si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
			si.wShowWindow = SW_HIDE;
			si.hStdOutput = handles.write;
			si.hStdError = handles.write;

			PROCESS_INFORMATION	pi;
			char * cl = new char[exe_path.length() + 1 + argus_.length() + 1];	// 最初の+1はスペースの分。最後の+1は終端文字の分。
			strcpy(cl, exe_path.c_str());
			strcat(cl, " ");	// スペースを追加
			strcat(cl, argus_.c_str());
			if (CreateProcess(NULL, cl, NULL, NULL, true, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi) == 0) return;
			if (WaitForSingleObject(pi.hProcess, timeout_) != WAIT_OBJECT_0) return;
			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
			fw_delarr(cl);

			DWORD len;
			if (PeekNamedPipe(handles.read, NULL, 0, NULL, &len, NULL) == 0) return;

			fw_delarr(str);
			str = new char[len + 1];
			str[len] = '\0';
			if (len > 0 && ReadFile(handles.read, str, len, &len, NULL) == 0) return;

			succeeded = true;
		}

		Exeexe & begin()
		{
			mythread.begin(get_message_system, this);
			return *this;
		}

		bool working() const { return mythread.working(); }

		bool ifsucceeded() const { return succeeded; }
		bool iffailed() const { return !ifsucceeded(); }

		const char * result() const { return str; }

		~Exeexe(){ fw_delarr(str); }



	private:
		class Handles
		{
		public:

			HANDLE read, write;
			Handles()
			{
				read = NULL;
				write = NULL;
			}
			~Handles()
			{
				if (read != NULL) CloseHandle(read);
				if (write != NULL) CloseHandle(write);
			}
		};

		char* str;
		DWORD timeout_;
		bool succeeded;
		std::string exe_path;
		std::string argus_;
		fw::thread mythread;

		static fw_thread_ get_message_system(void * param)
		{
			Exeexe & me = *(fw::pointer_cast<Exeexe *>(param));
			me.get_message();
			return 0;
		}

	};

}