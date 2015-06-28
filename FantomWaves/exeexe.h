#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "thread.h"

#pragma warning(disable : 4996)

namespace fw
{

	class exeexe
	{
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
		DWORD Timeout;
		bool succeeded;
		std::string Exepath;
		std::string Argus;
		fw::thread mythread;

		static fw_thread_ GetCUIAppMsgForThread(void * param)
		{
			exeexe & me = *(fw::pointer_cast<exeexe *>(param));
			me.GetCUIAppMsg();
			return 0;
		}

	public:

		exeexe()
		{
			str = NULL;
			Timeout = INFINITE;
		}

		exeexe & timeout(const DWORD timeout)
		{
			Timeout = timeout;
			return *this;
		}

		exeexe & exepath(const char * path)
		{
			Exepath = fw::cnct() << '\"' << path < '\"';
			return *this;
		}
		exeexe & exepath(const std::string & path)
		{
			Exepath = fw::cnct() << '\"' << path < '\"';
			return *this;
		}
		exeexe & _exepath(const char * path)
		{
			Exepath = path;
			return *this;
		}
		exeexe & _exepath(const std::string & path)
		{
			Exepath = path;
			return *this;
		}

		exeexe & argus(const char * path)
		{
			Argus = path;
			return *this;
		}
		exeexe & argus(const std::string & path)
		{
			Argus = path;
			return *this;
		}

		void GetCUIAppMsg()
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
			char * cl = new char[Exepath.length() + 1 + Argus.length() + 1];	// 最初の+1はスペースの分。最後の+1は終端文字の分。
			strcpy(cl, Exepath.c_str());
			strcat(cl, " ");	// スペースを追加
			strcat(cl, Argus.c_str());
			if (CreateProcess(NULL, cl, NULL, NULL, true, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi) == 0) return;
			if (WaitForSingleObject(pi.hProcess, Timeout) != WAIT_OBJECT_0) return;
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

		exeexe & begin()
		{
			mythread.begin(GetCUIAppMsgForThread, this);
			return *this;
		}

		bool working() const { return mythread.working(); }

		bool ifsucceeded() const { return succeeded; }
		bool iffailed() const { return !ifsucceeded(); }

		const char * result() const { return str; }

		~exeexe(){ fw_delarr(str); }
	};

}