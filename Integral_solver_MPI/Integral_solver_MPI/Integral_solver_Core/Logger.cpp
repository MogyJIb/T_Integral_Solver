#define _CRT_SECURE_NO_WARNINGS
#include<ctime>
#include "Logger.h"

using namespace std;

tstring Logger::path;

Logger::Logger() {
	init(
		path.empty()
		? _T("logfile.txt")
		: tstring(path).append(_T("logfile.txt")).data()
	);
}

Logger::Logger(const TCHAR *filename) {
	init(filename);
}

Logger::Logger(tstring path) {
	Logger::path = path;
	init(
		path.empty()
		? _T("logfile.txt")
		: tstring(path).append(_T("logfile.txt")).data()
	);
}

void Logger::init(const TCHAR* filename) {
	try {
		if (!_fhnd.is_open())
		{
			_fhnd.open(filename, tofstream::out | tofstream::app);
			_tcscpy(_dt_fmt, _T("[%Y-%m-%d %H:%M:%S]"));
		}
	}
	catch (const std::exception& e)
	{
		tcout << _T("Exception!!! ") << endl;
	}
}

Logger::~Logger() {
	_fhnd.close();
}

void Logger::setDateFormat(TCHAR *fmt) {
	_tcscpy(_dt_fmt, fmt);
}

//GetTimeStamp obtains the current timestamp and formats to "[2014-09-28 22:12:59]" form
tstring Logger::getTimeStamp() {
	TCHAR buff[100];
	time_t t = time(nullptr);
	tm tm;
	localtime_s(&tm, &t);
	tcsftime(buff, sizeof(buff), _dt_fmt, &tm);
	return tstring(buff);
}

tstring Logger::getLoglevelString(loglevel level) {
	tstring lvlstr{};
	switch (level) {
	case LOGWARN: lvlstr = _T("WARN: "); break;
	case LOGERROR: lvlstr = _T("ERROR: "); break;
	case LOGINFO: lvlstr = _T("INFO: "); break;
	}
	return lvlstr;
}

void Logger::log(loglevel level, tstring message) {
	_fhnd << getTimeStamp() << " " << getLoglevelString(level) << message << endl;
}

void Logger::logI(tstring message) {
	log(LOGINFO, message);
}

void Logger::logE(tstring message) {
	log(LOGERROR, message);
}

void Logger::logW(tstring message) {
	log(LOGWARN, message);
}