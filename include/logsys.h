#pragma once

#include<iostream>
#include<string>
#include<ctime>
#include<Windows.h>

#include"common.h"
#include"debugprint.h"

using namespace std;

#define PATH_DELIMITER '\\'

#define INFO_COMMONMSG 0
#define INFO_WARNING 1
#define INFO_ERROR 2
#define INFO_FATAL 3
#define INFO_CATEGORYUNDEFINED 4

#define S_STDOUT 0
#define S_STDERR 1

class MCDRCPPLog {
public:
	int stdfuncallconv InitLogSystem(string logfilefolder);
	int stdfuncallconv WriteLog(const char* buf, int size);
	HANDLE stdfuncallconv RawLogFileHandle();	//could be unsafe
	void Final();
	MCDRCPPLog();
	~MCDRCPPLog();
private:
	HANDLE LogFileHandle;
};

class OutputInterface {
public:
	int stdfuncallconv Init(string logfilepath);
	int stdfuncallconv Output(const char* outstr, const char* msger, int msgtype = INFO_COMMONMSG, int stream = S_STDOUT, bool nextline = true);

	int stdfuncallconv msg(const char* outstr, const char* msger = "MCDRCPP");
	int stdfuncallconv warning(const char* outstr, const char* msger = "MCDRCPP");
	int stdfuncallconv error(const char* outstr, const char* msger = "MCDRCPP");
	int stdfuncallconv fatal(const char* outstr, const char* msger = "MCDRCPP");
	int stdfuncallconv undef(const char* outstr, const char* msger = "MCDRCPP");

	int stdfuncallconv msg(string outstr, string msger = "MCDRCPP");
	int stdfuncallconv warning(string outstr, string msger = "MCDRCPP");
	int stdfuncallconv error(string outstr, string msger = "MCDRCPP");
	int stdfuncallconv fatal(string outstr, string msger = "MCDRCPP");
	int stdfuncallconv undef(string outstr, string msger = "MCDRCPP");

	int stdfuncallconv mlout(const char* en_US, const char* zh_CN, int msgtype = INFO_COMMONMSG, const char* msger = "MCDRCPP", int stream = S_STDOUT);
	int stdfuncallconv mlout(string en_US, string zh_CN, int msgtype = INFO_COMMONMSG, string msger = "MCDRCPP", int stream = S_STDOUT);

	OutputInterface();
private:
	string stdfuncallconv makefinastr(const char* outstr, const char* msger, int msgtype = INFO_COMMONMSG);
	//static MCDRCPPLog LogSys;
};

