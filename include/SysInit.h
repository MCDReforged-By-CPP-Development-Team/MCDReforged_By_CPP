/*
SysInit.h
��ͷ�ļ�Ӧ������Initialize()��Finalize()������������SysInit.cpp����Ҫ��includeԤ�������
*/
#pragma once

#include<string>
#include<Windows.h>
#include<iostream>

#include"common.h"
#include"debugprint.h"
#include"redirectstdio.h"

using namespace std;

int stdfuncallconv Initialize();
int stdfuncallconv Finalize();
int stdfuncallconv DetectDir();
int stdfuncallconv WelcomeMessage();
int stdfuncallconv OpenServer();