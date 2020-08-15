#pragma once
#ifndef LOGSYS_H
#define LOGSYS_H
#endif 
#include <iostream>
#include<string>
#include<stdio.h>
#include <io.h>
#include <direct.h>
#include<ctime>

#define PATH_DELIMITER '\\'

#define INFO 0
#define WARN 1
#define ERR 2

struct LOGSYS
{
private:
	int SetLogFile(FILE *file , const char* str, const char* InfType);
public:
	int SetSTDOUT(const char* str,int InformationType);
	int MakeLogFloderExists();
};
