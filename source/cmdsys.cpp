﻿#include"cmdsys.h"

extern vector<MCDRCommand> MCDRCommandQueue;

int stdfuncallconv MCDRCommand::AnalyzeCommand(string command) {
	return 0;
}

int stdfuncallconv MCDRCommand::ExecCommand(PMCDRCommand command)
{
	return 0;
}

MCDRCommand::MCDRCommand(string command) {
	this->rawText = command;
	this->isexecuted = false;
}

int stdfuncallconv NewMCDRCommand(string command)
{
	MCDRCommand cmd(command);
	MCDRCommandQueue.push_back(cmd);
	return 0;
}