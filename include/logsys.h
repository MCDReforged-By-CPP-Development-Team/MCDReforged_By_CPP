#pragma once

#include<iostream>
#include<string>
#include<ctime>
#include<Windows.h>

#include"common.h"
#include"cfgfile.h"

using namespace std;

#define PATH_DELIMITER '\\'

#define INFO_COMMONMSG 0
#define INFO_WARNING 1
#define INFO_ERROR 2
#define INFO_FATAL 3
#define INFO_CATEGORYUNDEFINED 4

#define STDOUT 0
#define STDERR 1

class MCDRCPPLog {
public:
	int stdfuncallconv InitLogSystem();
	int stdfuncallconv WriteLog();
	HANDLE stdfuncallconv RawLogFileHandle();	//could be unsafe
private:
	int stdfuncallconv CreateLogFile();
	HANDLE LogFileHandle;
};

class OutputInterface {
public:
	int stdfuncallconv Output(const char* outstr, const char* msger, int msgtype = INFO_COMMONMSG, int stream = STDOUT);

	int stdfuncallconv msg(const char* outstr);
	int stdfuncallconv warning(const char* outstr);
	int stdfuncallconv error(const char* outstr);
	int stdfuncallconv fatal(const char* outstr);
	int stdfuncallconv undef(const char* outstr);

	int stdfuncallconv msg(string outstr);
	int stdfuncallconv warning(string outstr);
	int stdfuncallconv error(string outstr);
	int stdfuncallconv fatal(string outstr);
	int stdfuncallconv undef(string outstr);
};