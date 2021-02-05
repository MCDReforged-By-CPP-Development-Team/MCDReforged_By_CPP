#pragma once

#include<string>
#include<vector>

#include"common.h"
#include"cfgfile.h"
#include"debugprint.h"

using namespace std;

class MCDRCommand {
public:
	string rawText;
	int stdfuncallconv ExecCommand();
	MCDRCommand(string command);
private:
	bool isexecuted;
};

typedef MCDRCommand* PMCDRCommand;

int stdfuncallconv NewMCDRCommand(string command);
int stdfuncallconv ExecCmdQueue();
