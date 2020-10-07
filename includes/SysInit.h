/*
SysInit.h
此头文件应当包含Initialize()和Finalize()函数的声明及SysInit.cpp所需要的include预编译语句
*/
#pragma once

#include"common.h"

#include<string>
#include<Windows.h>
#include<iostream>

using namespace std;

int stdfuncallconv Initialize();

int stdfuncallconv Finalize();

int stdfuncallconv GetJvmPath(string* strPath);

int stdfuncallconv InitDebugPrint(string str);