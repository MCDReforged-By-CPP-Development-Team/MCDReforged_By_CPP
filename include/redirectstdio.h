#pragma once
#include<Windows.h>
#include"common.h"
#include"cfgfile.h"
#include"debugprint.h"
#include"processoutput.h"

using namespace std;

#define NEWBUFFERSIZE 0x100

struct RedirectInformation;

typedef RedirectInformation REDIRECT_INFORMATION;
typedef RedirectInformation* PREDIRECT_INFORMATION;

int stdfuncallconv OpenServerAndRedirectIO(PREDIRECT_INFORMATION priInformation);
int stdfuncallconv CloseRedirect(PREDIRECT_INFORMATION priInformation, PINT TerminateProcessReturn);

#pragma region StructRedirectInformation

struct RedirectInformation
{

	HANDLE hStdInRead = NULL;   //子进程用的stdin的读入端  
	HANDLE hStdOutWrite = NULL; //子进程用的stdout的写入端  
	HANDLE hStdErrWrite = NULL; //子进程用的stderr的写入端  

	HANDLE hStdInWrite = NULL;  //主程序用的stdin的写入端  
	HANDLE hStdOutRead = NULL;  //主程序用的stdout的读入端  

	PROCESS_INFORMATION pi;
};

#pragma endregion


