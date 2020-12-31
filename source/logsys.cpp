#include "logsys.h"
#include"cfgfile.h"
#include "colorlog.h"
using namespace std;

MCDRCPPLog LogSys;

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

int stdfuncallconv OutputInterface::Init(string logfilepath)
{
	return LogSys.InitLogSystem(logfilepath);
}

int stdfuncallconv OutputInterface::Output(const char* outstr, const char* msger, int msgtype, int stream)
{
	
	int iret=0;

	HANDLE hCon;
	//hCon=GetStdHandle(STD_INPUT_HANDLE)
	LPSTR lpOut;
	DWORD dwWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbiOldInfo;
	ColorLog log;
	time_t t = time(0);
	char time[64];
	strftime(time, sizeof(time), "%Y-%m-%d/%H:%M:%S", localtime(&t));
	switch (stream)
	{
	case S_STDOUT:
		hCon = GetStdHandle(STD_OUTPUT_HANDLE);
		break;
	case S_STDERR:
		hCon = GetStdHandle(STD_ERROR_HANDLE);
		break;
	default:
		break;
	}
	GetConsoleScreenBufferInfo(hCon, &csbiOldInfo);
	lpOut = "[";
	WriteFile(hCon, lpOut, strlen(lpOut), &dwWritten, NULL);
	iret += dwWritten;
	//strcpy(lpOut, msger);
	WriteFile(hCon, msger, strlen(msger), &dwWritten, NULL);
	iret += dwWritten;
	WriteFile(hCon, "/",1, &dwWritten, NULL);
	iret += dwWritten;
	switch (msgtype)
	{
	case INFO_COMMONMSG:
		iret+= log.out("COMMON", GREEN_FOREGROUND);
		break;
	case INFO_WARNING:
		iret+= log.out("WARN", YELLOW_FOREGEOUND);
		break;
	case INFO_ERROR:
		iret+=log.out("ERROR", RED_FOREGROUND);
		break;
	case INFO_FATAL:
		iret+=log.out("FATAL", BACKGROUND_INTENSITY | BACKGROUND_RED | WHITE);
		break;
	case INFO_CATEGORYUNDEFINED:
		iret+=log.out("UNDEF", WHITE);
		break;
	default:
		break;
	}
	WriteFile(hCon, "]",1, &dwWritten, NULL);
	iret += dwWritten;
	WriteFile(hCon, outstr, strlen(outstr), &dwWritten, NULL);
	iret += dwWritten;
	WriteFile(hCon, "\n", 1, &dwWritten, NULL);
	iret += dwWritten;
	/*

