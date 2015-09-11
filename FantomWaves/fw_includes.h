#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif
#ifndef OEMRESOURCE
#define OEMRESOURCE
#endif
#ifndef STRICT
#define STRICT
#endif
#include <windows.h>
#include <Winuser.h>
#include <imagehlp.h>
#pragma comment(lib, "imagehlp.lib")
#include <string>
#include <map>
#include <vector>
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string.h>
#include <tchar.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#include <new>
#include <stdexcept>
#include <direct.h>
#include <memory.h>
#pragma comment( lib, "kernel32.lib" )
#pragma comment( lib, "user32.lib" )
#include <shlobj.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32")
