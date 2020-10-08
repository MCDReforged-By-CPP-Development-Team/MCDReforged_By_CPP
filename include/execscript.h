#pragma once

#include<vector>
#include<string>
#include<Windows.h>

using namespace std;

struct Script {
	int scriptType;
	string scriptNamr;
	string scriptPath;
	HANDLE scriptHandle;
};