#pragma once


#include <io.h>
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <iostream> 
#include <direct.h>
#include<vector>

using namespace std;


extern int _fastcall FilesRead(string root, vector<string>& fileVec);
