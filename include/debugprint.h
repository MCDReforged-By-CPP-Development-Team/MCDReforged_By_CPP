#pragma once

#include<string>
#include<iostream>
#include<ctime>

#include"common.h"

#define DEBUGPRINTSTR "[DebugPrint]"

using namespace std;

int stdfuncallconv DebugPrint(const char* outstr);
int stdfuncallconv DebugPrint(string outstr);
int stdfuncallconv DebugPrint(int outstr);
int stdfuncallconv DebugPrint(double outstr);