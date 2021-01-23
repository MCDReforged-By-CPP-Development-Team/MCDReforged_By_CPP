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
		hCon = GetStdHandle(STD_OUTPUT_HANDLE);
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

	if (stream == S_STDOUT) {
		iret = _output(finastr, S_STDOUT);

	}
	else if (stream == S_STDERR) {
		iret = _output(finastr, S_STDERR);
	}
	else {
		iret = _output(finastr, S_STDOUT);
	}
	*/
	string finalstr = makefinastr(outstr, msger, msgtype);
	LogSys.WriteLog(finalstr.c_str(), finalstr.size());
	return iret;
}

int stdfuncallconv OutputInterface::msg(const char* outstr, const char* msger)
{
	return Output(outstr, msger, INFO_COMMONMSG, S_STDOUT);
}

int stdfuncallconv OutputInterface::warning(const char* outstr, const char* msger)
{
	return Output(outstr, msger, INFO_WARNING, S_STDERR);
}

int stdfuncallconv OutputInterface::error(const char* outstr, const char* msger)
{
	return Output(outstr, msger, INFO_ERROR, S_STDERR);
}

int stdfuncallconv OutputInterface::fatal(const char* outstr, const char* msger)
{
	return Output(outstr, msger, INFO_FATAL, S_STDERR);
}

int stdfuncallconv OutputInterface::undef(const char* outstr, const char* msger)
{
	return Output(outstr, msger, INFO_CATEGORYUNDEFINED, S_STDOUT);
}

int stdfuncallconv OutputInterface::msg(string outstr, string msger)
{
	return Output(outstr.c_str(), msger.c_str(), INFO_COMMONMSG, S_STDOUT);
}

int stdfuncallconv OutputInterface::warning(string outstr, string msger)
{
	return Output(outstr.c_str(), msger.c_str(), INFO_WARNING, S_STDERR);
}

int stdfuncallconv OutputInterface::error(string outstr, string msger)
{
	return Output(outstr.c_str(), msger.c_str(), INFO_ERROR, S_STDERR);
}

int stdfuncallconv OutputInterface::fatal(string outstr, string msger)
{
	return Output(outstr.c_str(), msger.c_str(), INFO_FATAL, S_STDERR);
}

int stdfuncallconv OutputInterface::undef(string outstr, string msger)
{
	return Output(outstr.c_str(), msger.c_str(), INFO_CATEGORYUNDEFINED, S_STDOUT);
}

int stdfuncallconv OutputInterface::mlout(const char* en_US, const char* zh_CN, int msgtype, const char* msger, int stream)
{
	Settings GlobalSettings;
	if (GlobalSettings.GetInt(lang) == LANG_EN_US) {
		return Output(en_US, msger, msgtype, stream);
	}
	else if (GlobalSettings.GetInt(lang) == LANG_ZH_CN) {
		return Output(zh_CN, msger, msgtype, stream);
	}
	return 0;
}

int stdfuncallconv OutputInterface::mlout(string en_US, string zh_CN, int msgtype, string msger, int stream)
{
	Settings GlobalSettings;
	if (GlobalSettings.GetInt(lang) == LANG_EN_US) {
		return Output(en_US.c_str(), msger.c_str(), msgtype, stream);
	}
	else if (GlobalSettings.GetInt(lang) == LANG_ZH_CN) {
		return Output(zh_CN.c_str(), msger.c_str(), msgtype, stream);
	}
	return 0;
}

OutputInterface::OutputInterface()
{
	Settings set;
	if ( LogSys.RawLogFileHandle() == NULL ) LogSys.InitLogSystem(set.GetString(logpath));
}

string stdfuncallconv OutputInterface::makefinastr(const char* outstr, const char* msger, int msgtype)
{
	string finalstr;
	time_t t = time(0);
	char time[64];
	strftime(time, sizeof(time), "%Y-%m-%d/%H:%M:%S", localtime(&t));

	finalstr.append("[");
	finalstr.append(msger);
	switch (msgtype)
	{
	case INFO_COMMONMSG:
		finalstr.append("/COMMON");
		break;
	case INFO_WARNING:
		finalstr.append("/WARN");
		break;
	case INFO_ERROR:
		finalstr.append("/ERROR");
		break;
	case INFO_FATAL:
		finalstr.append("/FATAL");
		break;
	case INFO_CATEGORYUNDEFINED:
		finalstr.append("/UNCATE");
		break;
	default:
		finalstr.append("/UNCATE");
		break;
	}
	finalstr.append("]");
	finalstr.append("[");
	finalstr.append(time);
	finalstr.append("]");

	finalstr.append(outstr);
	finalstr.append("\r\n");
	return finalstr;
}
//<<<<<<< HEAD

int stdfuncallconv OutputInterface::_output(string finalstr, int stream, LPDWORD bytewrittentostdout, int* writefileret)
{
	HANDLE stdouthan, stderrhan;
	stdouthan = GetStdHandle(STD_OUTPUT_HANDLE);
	stderrhan = GetStdHandle(STD_ERROR_HANDLE);
	int iret;
	DWORD bytewritten;
	if (bytewrittentostdout == NULL || writefileret == NULL) {
		if (stream == S_STDOUT) {
			iret = LogSys.WriteLog(finalstr.c_str(), finalstr.size());
			WriteFile(stdouthan, finalstr.c_str(), finalstr.length(), &bytewritten, NULL);
		}
		else {
			iret = LogSys.WriteLog(finalstr.c_str(), finalstr.size());
			WriteFile(stderrhan, finalstr.c_str(), finalstr.length(), &bytewritten, NULL);
		}
	}
	else if (bytewrittentostdout != NULL && writefileret != NULL) {
		if (stream == S_STDOUT) {
			iret = LogSys.WriteLog(finalstr.c_str(), finalstr.size());
			*writefileret = WriteFile(stdouthan, finalstr.c_str(), finalstr.length(), &bytewritten, NULL);
			*bytewrittentostdout = bytewritten;
		}
		else {
			iret = LogSys.WriteLog(finalstr.c_str(), finalstr.size());
			*writefileret = WriteFile(stderrhan, finalstr.c_str(), finalstr.length(), &bytewritten, NULL);
			*bytewrittentostdout = bytewritten;
		}
	}
	else {
		if (stream == S_STDOUT) {
			iret = LogSys.WriteLog(finalstr.c_str(), finalstr.size());
			WriteFile(stdouthan, finalstr.c_str(), finalstr.length(), &bytewritten, NULL);
		}
		else {
			iret = LogSys.WriteLog(finalstr.c_str(), finalstr.size());
			WriteFile(stderrhan, finalstr.c_str(), finalstr.length(), &bytewritten, NULL);
		}
	}
	return iret;
}
//=======
//>>>>>>> be791b1a4e8227563b51fc27e15dff5ea423a208
