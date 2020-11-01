#include "logsys.h"

using namespace std;

int stdfuncallconv MCDRCPPLog::InitLogSystem()
{
	time_t t = time(0);
	char logfilename[64];
	strftime(logfilename, sizeof(logfilename), "%Y-%m-%d-%H-%M-%S", localtime(&t)); //年-月-日-时-分-秒

	string logfilepath = strLogFilePath + "\\" + logfilename;
	LogFileHandle = CreateFile(logfilepath.c_str()
		, GENERIC_READ|GENERIC_WRITE
		, FILE_SHARE_READ
		, NULL
		, OPEN_ALWAYS
		, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN|FILE_FLAG_WRITE_THROUGH
		, NULL);

	if(LogFileHandle != 0)
		return 0;
	return -1;
}

int stdfuncallconv MCDRCPPLog::WriteLog()
{
	return 0;
}

HANDLE stdfuncallconv MCDRCPPLog::RawLogFileHandle()
{
	return LogFileHandle;
}

int stdfuncallconv MCDRCPPLog::CreateLogFile()
{
	return 0;
}

int stdfuncallconv OutputInterface::Output(const char* outstr, const char* msger, int msgtype, int stream)
{
	return 0;
}

int stdfuncallconv OutputInterface::msg(const char* outstr)
{
	return 0;
}

int stdfuncallconv OutputInterface::warning(const char* outstr)
{
	return 0;
}

int stdfuncallconv OutputInterface::error(const char* outstr)
{
	return 0;
}

int stdfuncallconv OutputInterface::fatal(const char* outstr)
{
	return 0;
}

int stdfuncallconv OutputInterface::undef(const char* outstr)
{
	return 0;
}

int stdfuncallconv OutputInterface::msg(string outstr)
{
	return 0;
}

int stdfuncallconv OutputInterface::warning(string outstr)
{
	return 0;
}

int stdfuncallconv OutputInterface::error(string outstr)
{
	return 0;
}

int stdfuncallconv OutputInterface::fatal(string outstr)
{
	return 0;
}

int stdfuncallconv OutputInterface::undef(string outstr)
{
	return 0;
}
