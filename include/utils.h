#pragma once

#include"common.h"
#include<vector>
#include<string>
#include<iostream>
#include<Windows.h>
using namespace std;

//��ָ���ַ���{pattern}��Ƭ{str}
vector<string> split(const string& str, const string& pattern);

//Ѱ���ļ����Ƿ���� strpath:Ŀ¼
//����true��Ϊ�ļ��д��� ����falseΪ�ļ��в����ڻ���Ϊ�ļ�
bool CheckFolderExist(const string& strPath);

