#pragma once

#include<string>
#include<vector>

#include"common.h"

using namespace std;

class MCDRCommand;
typedef MCDRCommand* pMCDRCommand;
vector<MCDRCommand> MCDRCommandQueue;

class MCDRCommand {
public:
	string rawText;
	int stdfuncallconv AnalyzeCommand(string command);
	int stdfuncallconv ExecCommand(pMCDRCommand command);
	MCDRCommand(string command);
private:
	bool isexecuted;
};

int stdfuncallconv NewMCDRCommand(string command);
