#include"cmdsys.h"
#pragma warning(ignore :26496)
vector<MCDRCommand> MCDRCommandQueue;

/*指令列表：
*  echo <string> //字面意思
*  stop //字面意思
*  restart //字面意思
* 
* 
* 
* 
* 
* 
*/


int stdfuncallconv MCDRCommand::ExecCommand()
{
	Settings set;
	string cmd = this->rawText;
	string prefix = set.GetString(insprefix);
	OutputInterface output;
	/*
	if (cmd.find_first_of(prefix) != 0) {
		this->isexecuted = true;
		return -1;
	}

	cmd.erase(0, prefix.length());
	dp(cmd);

	auto firstnotblank = cmd.find_first_not_of(" ");
	cmd.erase(0, firstnotblank);
	dp(cmd);
	vector<string> cmds = split(cmd, " ");

	//处理完成 下一步就是继续分析指令*/
	if (cmd.length() != 0)
	{
		vector<string> cmds = split(cmd, " ");
		vector<string>::iterator it;
		string cmd_echo = "echo";
		if (cmds[0] == prefix)//是否是mcdrcpp命令
		{
			if (cmds[1] == "echo")
			{
				cmds = del(cmds, prefix);
				cmds = del(cmds, cmd_echo);
				for (it = cmds.begin() ;it != cmds.end();it++)
				{
					output.msg(*it);
				}
				return 0;
			}
			else
			{
				if (true)
				{

				}
				else
				{
					if (true)
					{

					}
					else
					{

					}
				}
			}
		}
		else
		{
			//在这里写插件相关指令
			//将命令作为消息传入python插件
			//在注册的指令中寻找
			return 0;
		}
	}


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

int stdfuncallconv ExecCmdQueue()
{
	for (vector<MCDRCommand>::iterator iter = MCDRCommandQueue.begin(); iter != MCDRCommandQueue.end(); iter++)
	{
		iter->ExecCommand();
	}
	return 0;
}
