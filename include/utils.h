#pragma once

#include"common.h"
#include<vector>
#include<string>
#include<iostream>
#include<Windows.h>
using namespace std;

//用指定字符串{pattern}切片{str}
vector<string> split(const string& str, const string& pattern);

//寻找文件夹是否存在 strpath:目录
//返回true即为文件夹存在 返回false为文件夹不存在或者为文件
bool CheckFolderExist(const string& strPath);

//从vector中删除指定的某一个元素 
template<class T1, class T2> vector<T1> del(vector<T1> a, T2 to_be_removed_obj);

//列出指定路径下的所有文件
vector<string> stdfuncallconv ListFiles(string path);


//列出指定路径下带有指定扩展名的所有文件
vector<string> stdfuncallconv ListFiles(string path,string ext);

//字符串a中含有字符串b
bool have(string a, string b);
