#pragma once
#include<Windows.h>
#include"common.h"
#include"cfgfile.h"
#include"debugprint.h"
#include"processoutput.h"

using namespace std;

#define NEWBUFFERSIZE 0x100

typedef RedirectInformation REDIRECT_INFORMATION;
typedef RedirectInformation* PREDIRECT_INFORMATION;

int stdfuncallconv OpenServerAndRedirectIO(PREDIRECT_INFORMATION priInformation);
int stdfuncallconv CloseRedirect(PREDIRECT_INFORMATION priInformation);

#pragma region StructRedirectInformation

struct RedirectInformation
{

	HANDLE hStdInRead = NULL;   //�ӽ����õ�stdin�Ķ����  
	HANDLE hStdOutWrite = NULL; //�ӽ����õ�stdout��д���  
	HANDLE hStdErrWrite = NULL; //�ӽ����õ�stderr��д���  

	HANDLE hStdInWrite = NULL;  //�������õ�stdin��д���  
	HANDLE hStdOutRead = NULL;  //�������õ�stdout�Ķ����  

	RedirectInformation& operator=(RedirectInformation a) {
		this->hStdErrWrite = a.hStdErrWrite;
		this->hStdInRead = a.hStdInRead;
		this->hStdInWrite = a.hStdInWrite;
		this->hStdOutRead = a.hStdOutRead;
		this->hStdOutWrite = a.hStdOutWrite;
	}
};

#pragma endregion


