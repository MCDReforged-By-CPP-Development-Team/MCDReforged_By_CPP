#pragma once

#include<string>
#ifndef H_CMDSYS
#define H_CMDSYS

#include<vector>
#include<Windows.h>

#include"globaldef.h"
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

	int stdfuncallconv echo(vector<string> str);
	int stdfuncallconv status();
	int stdfuncallconv reloads();
	int stdfuncallconv permission();
	int stdfuncallconv plugins();
	
	int stdfuncallconv mccmdqueue();

	int stdfuncallconv help();
	const string cmd_echo = "echo";

};

typedef MCDRCommand* PMCDRCommand;

int stdfuncallconv NewMCDRCommand(string command);
int stdfuncallconv ExecCmdQueue();

#endif // !H_CMDSYS