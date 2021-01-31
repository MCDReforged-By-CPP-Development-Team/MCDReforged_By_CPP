#pragma once
#include<Windows.h>
#include"common.h"
#include"cfgfile.h"
#include"debugprint.h"
#include"processoutput.h"

using namespace std;

#define NEWBUFFERSIZE 0x100

int stdfuncallconv OpenServerAndRedirectIO();