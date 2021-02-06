#pragma once

#include<string>
#include<vector>
#include<Windows.h>
#include"common.h"
#include"cfgfile.h"
#include"debugprint.h"
#include"utils.h"

using namespace std;

class MCDRCommand {
public:
	string rawText;
	int stdfuncallconv ExecCommand();
	MCDRCommand(string command);
private:
	bool isexecuted;
	int stdfuncallconv status();
	int stdfuncallconv reloads();
	int stdfuncallconv permission();
	int stdfuncallconv plugins();
	
	int stdfuncallconv mccmdqueue();

	int stdfuncallconv help();
};

typedef MCDRCommand* PMCDRCommand;

int stdfuncallconv NewMCDRCommand(string command);
int stdfuncallconv ExecCmdQueue();
