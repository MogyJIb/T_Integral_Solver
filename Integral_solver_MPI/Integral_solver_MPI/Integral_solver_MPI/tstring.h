#pragma once

#include <tchar.h>
#include <xstring>
#include <iostream>
#include <time.h>
#include <wchar.h>

#ifdef _UNICODE

typedef std::wstring tstring;
typedef std::wofstream tofstream;

#define to_tstring(x) std::to_wstring(x)
#define tcout std::wcout
#define tcout std::wcout
#define tcsftime(str, maxsize, format, timedate) wcsftime(str, maxsize, format, timedate)

#else

typedef std::string tstring;
typedef std::ofstream tofstream;

#define to_tstring(x) std::to_string(x)
#define tcout std::cout
#define tcsftime(str, maxsize, format, timedate) strftime(str, maxsize, format, timedate)

#endif

