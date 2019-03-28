#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<mutex>

#include "tstring.h"

class Logger
{

	static tstring path;

public:
	enum loglevel { LOGWARN, LOGERROR, LOGINFO };
	tofstream _fhnd;

	void setDateFormat(TCHAR*);
	void logI(tstring);
	void logE(tstring);
	void logW(tstring);

	Logger(tstring path);
	Logger();
	Logger(const TCHAR*);
	~Logger();

private:
	TCHAR _dt_fmt[512];
	const std::vector<tstring>_loglevel_text;
	tstring getTimeStamp();
	tstring getLoglevelString(loglevel);
	void log(loglevel, tstring);
	void init(const TCHAR*);
};

