#pragma once

#include<string>
#include<iostream>
#include<ctime>

#include"common.h"

#define DEBUGPRINTSTR "[DebugPrint]"
#ifdef DEBUG_FUNC_ENABLE
#define dp(out) DebugPrint(out)
#else
#define dp(out) ;
#endif // DEBUG_FUNC_ENABLE

using namespace std;

int stdfuncallconv DebugPrint(const char* outstr);
int stdfuncallconv DebugPrint(string outstr);
int stdfuncallconv DebugPrint(int outstr);
int stdfuncallconv DebugPrint(double outstr);