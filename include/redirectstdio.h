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

	HANDLE hStdInRead = NULL;   //�ӽ����õ�stdin�Ķ����  
	HANDLE hStdOutWrite = NULL; //�ӽ����õ�stdout��д���  
	HANDLE hStdErrWrite = NULL; //�ӽ����õ�stderr��д���  

	HANDLE hStdInWrite = NULL;  //�������õ�stdin��д���  
	HANDLE hStdOutRead = NULL;  //�������õ�stdout�Ķ����  

	PROCESS_INFORMATION pi;
};

#pragma endregion


