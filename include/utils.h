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

//��vector��ɾ��ָ����ĳһ��Ԫ�� 
template<class T1, class T2> vector<T1> del(vector<T1> a, T2 to_be_removed_obj);