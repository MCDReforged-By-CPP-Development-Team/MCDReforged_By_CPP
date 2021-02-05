#pragma once

#include<string>
#include<vector>

#include"common.h"

using namespace std;

class MCDRCommand {
public:
	string rawText;
	int stdfuncallconv AnalyzeCommand(string command);
	int stdfuncallconv ExecCommand(MCDRCommand* command);
	MCDRCommand(string command);
private:
	bool isexecuted;
};
typedef MCDRCommand* PMCDRCommand;

int stdfuncallconv NewMCDRCommand(string command);
