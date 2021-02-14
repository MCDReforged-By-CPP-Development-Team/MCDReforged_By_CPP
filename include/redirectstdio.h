#pragma once
#include<Windows.h>
#include<thread>
#include<vector>
#include"common.h"
#include"cfgfile.h"
#include"debugprint.h"
#include"processoutput.h"
using namespace std;

#define NEWBUFFERSIZE 0x100
#define BUFSIZE 4096

#pragma region StructRedirectInformation

struct RedirectInformation
{

	HANDLE hStdInRead = NULL;   //子进程用的stdin的读入端  
	HANDLE hStdInWrite = NULL;  //主程序用的stdin的读入端 

	HANDLE hStdOutRead = NULL;  //主程序用的stdout的读入端  
	HANDLE hStdOutWrite = NULL; //子进程用的stdout的写入端  

	HANDLE hStdErrWrite = NULL; //子进程用的stderr的写入端  

	RedirectInformation& operator=(RedirectInformation &a) {
		if (this != &a)
		{
			this->hStdErrWrite = a.hStdErrWrite;
			this->hStdInRead = a.hStdInRead;
			this->hStdInWrite = a.hStdInWrite;
			this->hStdOutRead = a.hStdOutRead;
			this->hStdOutWrite = a.hStdOutWrite;
			return *this;
		}
		else
		{
			exception e;
			throw e;
		}
	}
};

#pragma endregion


typedef RedirectInformation REDIRECT_INFORMATION;
typedef REDIRECT_INFORMATION *PREDIRECT_INFORMATION;

int stdfuncallconv OpenServerAndRedirectIO(PREDIRECT_INFORMATION priInformation);
DWORD stdfuncallconv ServerSTDOUT(REDIRECT_INFORMATION priInfo, HANDLE hProc);
int stdfuncallconv CloseRedirect(PREDIRECT_INFORMATION priInformation);
int stdfuncallconv WriteToPipe(const char* in_buffer, DWORD dwSize);

