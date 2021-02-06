#include"cmdsys.h"

vector<MCDRCommand> MCDRCommandQueue;

int stdfuncallconv MCDRCommand::ExecCommand()
{
	Settings set;
	string cmd = this->rawText;
	string prefix = set.GetString(insprefix);

	if (cmd.find_first_of("!!help") == 0) {
		this->isexecuted = true;
		return -1;
	}
	if (cmd.find_first_of(prefix) != 0) {
		this->isexecuted = true;
		return -1;
	}

	cmd.erase(0, prefix.length());
	dp(cmd);

	auto firstnotblank = cmd.find_first_not_of(" ");
	cmd.erase(0, firstnotblank);
	dp(cmd);

	//处理完成 下一步就是继续分析指令
	return 0;
}

MCDRCommand::MCDRCommand(string command) {
	this->rawText = command;
	this->isexecuted = false;
}

#pragma region CMDs

int stdfuncallconv MCDRCommand::status()
{
	return 0;
}

int stdfuncallconv MCDRCommand::reloads()
{
	return 0;
}

int stdfuncallconv MCDRCommand::permission()
{
	return 0;
}

int stdfuncallconv MCDRCommand::plugins()
{
	return 0;
}

int stdfuncallconv MCDRCommand::mccmdqueue()
{
	return 0;
}

int stdfuncallconv MCDRCommand::help()
{
	return 0;
}

#pragma endregion

int stdfuncallconv NewMCDRCommand(string command)
{
	MCDRCommand cmd(command);
	MCDRCommandQueue.push_back(cmd);
	return 0;
}

int stdfuncallconv ExecCmdQueue()
{
	for (vector<MCDRCommand>::iterator iter = MCDRCommandQueue.begin(); iter != MCDRCommandQueue.end(); iter++)
	{
		iter->ExecCommand();
	}
	return 0;
}
