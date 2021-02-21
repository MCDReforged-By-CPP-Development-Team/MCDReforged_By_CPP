#pragma once

#include"globaldef.h"

#include<vector>
#include<string>
#include<iostream>
#include<Windows.h>
#include<list>
#include<guiddef.h>
#include<strstream>

using namespace std;

//用指定字符串{pattern}切片{str}
vector<string> split(const string& str, const string& pattern);

//用指定字符串{pattern}切片{str}
list<string> splittolist(const string& str, const string& pattern);

//从字符串list生成字符串,以指定字符串分隔
string makestring(list<string> list_ , string spiliter);

//从字符串vector生成字符串,以指定字符串分隔
string makestring(vector<string> list_, string spiliter);

//寻找文件夹是否存在 strpath:目录
//返回true即为文件夹存在 返回false为文件夹不存在或者为文件
bool CheckFolderExist(const string& strPath);

//从vector中删除指定的某一个元素 
template<class T1, class T2> 
vector<T1> del(vector<T1> a, T2 to_be_removed_obj);

//列出指定路径下的所有文件
vector<string> stdfuncallconv ListFiles(string path);

//列出指定路径下带有指定扩展名的所有文件
vector<string> stdfuncallconv ListFiles(string path,string ext);

//字符串a中含有字符串b
bool stdfuncallconv have(string a, string b);

//生成GUID
string stdfuncallconv CreateGuid(GUID* pguid);

//比较MCDRCPP版本
int stdfuncallconv CompareVersion(string Ver1, string Ver2);

//获取用户输入字符串，以\n为结尾
string stdfuncallconv GetInputString();

//获取用户输入字符
CHAR stdfuncallconv GetInputChar();


