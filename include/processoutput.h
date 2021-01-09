#pragma once
#include"cppplugin.h"
#include"pyplugin.h"
#include"common.h"
#include"debugprint.h"

using namespace std;

int stdfuncallconv ProcessOutput(LPSTR output);
int stdfuncallconv _ProcessOutput(LPSTR output);
int stdfuncallconv DispatchPluginMsg(int* processresult);