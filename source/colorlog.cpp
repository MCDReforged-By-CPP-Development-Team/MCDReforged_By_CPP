#include "colorlog.h"



ColorLog::ColorLog()
{
}


int stdfuncallconv ColorLog::out(LPSTR sOut, WCHAR wTextAttribute)
{
	HANDLE hOutput;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	WORD wOldAttribute;
	DWORD dbWritten;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOutput, &csbiInfo);
	wOldAttribute = csbiInfo.wAttributes;
	SetConsoleTextAttribute(hOutput, wTextAttribute);
	WriteFile(hOutput, sOut, lstrlen(sOut), &dbWritten, NULL);
	SetConsoleTextAttribute(hOutput, wOldAttribute);

	return dbWritten;
}
