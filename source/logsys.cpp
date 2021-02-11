#include "logsys.h"
#include"cfgfile.h"
#include "colorlog.h"
using namespace std;

int stdfuncallconv MCDRCPPLog::InitLogSystem(string logfilefolder)
{
	DebugPrint("Enter InitLogSystem.");
	time_t t = time(0);
	char logfilename[64];
	strftime(logfilename, sizeof(logfilename), "%Y-%m-%d-%H-%M-%S", localtime(&t)); //��-��-��-ʱ-��-��
	string logfolder;
	logfolder.append(".\\").append(logfilefolder);
	dp(logfolder);
	dp(logfilefolder);

	auto bret = CreateDirectory(logfolder.c_str(), NULL);

	if (!bret)
		return -1;
	CloseHandle(LogFileHandle);
	dp("Successful in check/create log folder.");

	string logfilepath;
	logfilepath.append(".\\").append(logfilefolder).append("\\").append(logfilename).append(".log");
	dp(logfilepath);
	LogFileHandle = CreateFile(logfilepath.c_str()
		, GENERIC_READ|GENERIC_WRITE
		, FILE_SHARE_READ
		, NULL
		, OPEN_ALWAYS
		, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN|FILE_FLAG_WRITE_THROUGH
		, NULL);

	if(LogFileHandle !=NULL)
		return 0;
	dp("Error in creating log file.");
	return -1;
}

int stdfuncallconv MCDRCPPLog::WriteLog(const char* buf, int size)
{
	DWORD charwritten;
	auto error = WriteFile(LogFileHandle, buf, size, &charwritten, NULL);
	if (!error)return -1;
	dp((int)charwritten);
	return charwritten;
}

HANDLE stdfuncallconv MCDRCPPLog::RawLogFileHandle()
{
	return LogFileHandle;
}

void MCDRCPPLog::Final()
{
	CloseHandle(LogFileHandle);
}

MCDRCPPLog::MCDRCPPLog()
{
}

MCDRCPPLog::~MCDRCPPLog()
{
	CloseHandle(LogFileHandle);
}
