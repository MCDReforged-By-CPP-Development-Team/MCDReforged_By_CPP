#pragma once

#include<iostream>
#include<string>
#include<ctime>
#include<Windows.h>

#include"globaldef.h"
#include"debugprint.h"

using namespace std;

#define PATH_DELIMITER '\\'

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
