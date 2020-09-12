#include "logsys.h"
#include <Windows.h>
#ifndef _CRT_SECURE_NO_WARNINGS
	#define _CRT_SECURE_NO_WARNINGS
#endif

#pragma warning(disable:4996)


using namespace std;


int stdfuncallconv LOGSYS::SetLogFile(FILE* file, const char* str,const char* InfType)
{
	time_t time_ = time(NULL);
	char t[50] = { 0 };
	strftime(t, sizeof(t), "%Y-%m-%d-%H-%M-%S", localtime(&time_));
	FILE* pf = NULL;
	pf = file;
	char* logname = NULL;
	char* tmp= NULL;
	tmp = strcat(t, ".mcdrlog");
	char dir[MAX_PATH];
	auto getcwdret = _getcwd(dir,MAX_PATH);
	logname = strcat(dir, "\\");
	tmp = strcat(logname,tmp);
	//cout << dir << endl;
	pf = fopen(tmp, "a+");
	if (fputs("[", pf) != EOF)
	{
		if (fputs(t, pf) != EOF)
		{
			if (fputs("]", pf) != EOF)
			{
				if (fputs("[", pf) != EOF)
				{
					if (fputs(InfType, pf) != EOF)
					{
						if (fputs("]", pf) != EOF)
						{
							if (fputs(str, pf) != EOF)
							{
								return 114514;
							}
							else
							{
								return -1;
							}
						}
					
					}
					
				}
				
			}
			
		}
		
	}
	fclose(pf);
	return 1;
}

int stdfuncallconv LOGSYS::SetSTDOUT(const char* str,int InformationType)
{
	time_t time_ = time(NULL);
	char t[50] = { 0 };
	strftime(t, sizeof(t), "%Y-%m-%d-%H-%M-%S", localtime(&time_));
	FILE* fp = NULL;
	cout << "[";
	cout << t;
	cout << "]";
	switch (InformationType)
	{
	case INFO:
		cout << "[";
		cout << "INFO";
		cout << "]";
		cout << "  ";
		cout << str;
		SetLogFile(fp, str, "INFO");
		break;
	case WARN:
		cout << "[";
		cout << "WARN";
		cout << "]";
		cout << "  ";
		cout << str;
		SetLogFile(fp, str, "WARN");
		break;
	case ERR:
		cout << "[";
		cout << "ERROR";
		cout << "]";
		cout << "  ";
		cout << str;
		SetLogFile(fp, str, "ERROR");
		break;
	default:
		return -134;
		break;
	}

	return 1;
}

int stdfuncallconv CreateDirectory(const string folder) {
	string folder_builder;
	string sub;
	sub.reserve(folder.size());
	for (auto it = folder.begin(); it != folder.end(); ++it) {
		const char c = *it;
		sub.push_back(c);
		if (c == PATH_DELIMITER || it == folder.end() - 1) {
			folder_builder.append(sub);
			if (0 != ::_access(folder_builder.c_str(), 0)) {
				// 没有此文件夹
				if (0 != ::_mkdir(folder_builder.c_str())) {
					// 创建文件夹失败
					return -1;
				}
			}
			sub.clear();
		}
	}
	return 1;
}

int stdfuncallconv LOGSYS::MakeLogFloderExists()
{
	int FileExists = access("logs", 0);
	if (FileExists == -1)
	{
		SetSTDOUT("找不到logs文件夹\n", WARN);
		if (CreateDirectory("logs") == 1)
		{
			SetSTDOUT("已创建logs文件夹\n", INFO);
			return 114514;

		}
		else
		{
			SetSTDOUT("无法创建logs文件夹\n", ERROR);
			return -114514;
		}
	}
	else
	{
		SetSTDOUT("找到logs文件夹\n", INFO);
		return 114514;
	}
	
}


