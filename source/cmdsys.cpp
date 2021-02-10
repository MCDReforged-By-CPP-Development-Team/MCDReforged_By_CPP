#include"cmdsys.h"

vector<MCDRCommand> MCDRCommandQueue;
OutputInterface logger;
int stdfuncallconv MCDRCommand::ExecCommand()
{
	Settings set;
	string cmd = this->rawText;
	string prefix = set.GetString(insprefix);
	vector<string> cmds;
	
	/*
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
	*/

	if (cmd.length() != 0) {
		cmds = split(cmd, " ");	//处理完成 下一步就是继续分析指令
	}
	else {
		return -1;
	}
	if (cmds.at(0) == prefix)
	{

	}
	else
	{
		//在cpp插件注册的命令中查找
		//否则作为消息送入py插件
	}

	if (cmds.at(1) == "plugins")//为啥不让用switch
	{
		plugins();
		return 0;
	}
	if (cmds.at(1) == "echo")
	{
		echo(cmds);
	}
	if (cmds.at(1) == "permissions")
	{

	}
	if (cmds.at(1) == "status")
	{

	}
	if (cmds.at(1) == "help")
	{

	}
	if (cmds.at(1) == "mccmdqueue")
	{

	}
	return 0;
}

MCDRCommand::MCDRCommand(string command) {
	this->rawText = command;
	this->isexecuted = false;
}

#pragma region CMDs

int stdfuncallconv MCDRCommand::echo(vector<string> str)
{
	OutputInterface log;
	string tmp;
	for (size_t i = 2; i < str.size(); i++)
	{
		if (str.at(i) != "")
		{
			tmp += str.at(i);
			tmp += " ";
		}
	}
	log.msg(tmp);
	return 0;
}

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
