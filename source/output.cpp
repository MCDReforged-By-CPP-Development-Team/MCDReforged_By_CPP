#include"output.h"
#include"logsys.h"
#include"systemfun.h"

MCDRCPPLog Log;

int stdfuncallconv OutputInterface::Init(string logfilepath)
{
	return Log.InitLogSystem(logfilepath);
}

int stdfuncallconv OutputInterface::Output(const char* outstr, const char* msger, int msgtype, int stream, bool nextline)
{

	int iret = 0;

	HANDLE hCon;
	//hCon=GetStdHandle(STD_INPUT_HANDLE)
	LPCSTR lpOut;
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
	WriteFile(hCon, "/", 1, &dwWritten, NULL);
	iret += dwWritten;
	switch (msgtype)
	{
	case INFO_COMMONMSG:
		iret += log.out("INFO", GREEN_FOREGROUND);
		break;
	case INFO_WARNING:
		iret += log.out("WARN", YELLOW_FOREGEOUND);
		break;
	case INFO_ERROR:
		iret += log.out("ERROR", RED_FOREGROUND);
		break;
	case INFO_FATAL:
		iret += log.out("FATAL", BACKGROUND_INTENSITY | BACKGROUND_RED | WHITE);
		break;
	case INFO_CATEGORYUNDEFINED:
		iret += log.out("UNDEF", WHITE);
		break;
	default:
		break;
	}
	WriteFile(hCon, "]", 1, &dwWritten, NULL);
	iret += dwWritten;
	WriteFile(hCon, outstr, strlen(outstr), &dwWritten, NULL);
	iret += dwWritten;
	if (nextline) WriteFile(hCon, "\n", 1, &dwWritten, NULL);
	iret += dwWritten;

	string finalstr = makefinastr(outstr, msger, msgtype);
	Log.WriteLog(finalstr.c_str(), finalstr.size());
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
	Output(outstr, msger, INFO_FATAL, S_STDERR);
	Finalize(-1);
	return 0;
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
	Output(outstr.c_str(), msger.c_str(), INFO_FATAL, S_STDERR);
	Finalize(-1);
	return 0;
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
		finalstr.append("/INFO");
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
//=======
//>>>>>>> be791b1a4e8227563b51fc27e15dff5ea423a208
