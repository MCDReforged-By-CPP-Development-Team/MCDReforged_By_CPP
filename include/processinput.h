#pragma once

#include<string>
#include<Windows.h>

#include"cfgfile.h"
#include"redirectstdio.h"
#include"common.h"
#include"debugprint.h"
#include"cmdsys.h"

using namespace std;

int stdfuncallconv ProcessInput(LPCSTR rawText);