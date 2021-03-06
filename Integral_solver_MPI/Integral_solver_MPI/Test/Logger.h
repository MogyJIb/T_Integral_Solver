#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<mutex>

#include "tstring.h"

class Logger
{
public:
	enum loglevel { LOGWARN, LOGERROR, LOGINFO };
	tofstream _fhnd;

	void setDateFormat(TCHAR*);
	void logI(tstring);
	void logE(tstring);
	void logW(tstring);

	Logger();
	Logger(const TCHAR*);
	~Logger();

private:
	bool file;
	TCHAR _dt_fmt[512];
	std::mutex _msemaphore;
	const std::vector<tstring>_loglevel_text;
	tstring getTimeStamp();
	tstring getLoglevelString(loglevel);
	void log(loglevel, tstring);
};