#include"minecraftcmdqueue.h"

list<MinecraftCommandQueueInfo> MinecraftCommandQueue;
/*
Minecraft指令队列集合(list)
	队列1Info 队列1(外层map)
				指令1Info 指令1(内层map)
				指令2Info 指令2
				...
				指令nInfo 指令n
	队列2Info 队列2
	...
	队列nInfo 队列n
*/

#pragma region queue

//队列操作
int stdfuncallconv NewCmdQueue(pMinecraftCommandQueueInfo info) {
	MinecraftCommandQueue.push_back(info);
	return 0;
}
int stdfuncallconv NewCmdQueue(const char* name) {
	MinecraftCommandQueueInfo info;
	info.execute = true;
	info.prioritylevel = CMD_PL_NORMAL;
	info.QueueName = name;

	MinecraftCommandQueue.push_back(info);
	return 0;
}
int stdfuncallconv NewCmdQueue(string name) {
	return NewCmdQueue(name.c_str());
}

int stdfuncallconv DeleteCmdQueue(const char* name) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if (iter->QueueName == name) {
			MinecraftCommandQueue.erase(iter);
		}
	}
	return 0;
}
int stdfuncallconv DeleteCmdQueue(string name) {
	return DeleteCmdQueue(name.c_str());
}

int stdfuncallconv QueryCmdQueue(const char* name, pMinecraftCommandQueueInfo info) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if (iter->QueueName == name) {
			info = iter;
		}
	}
	return 0;
}
int stdfuncallconv QueryCmdQueue(string name, pMinecraftCommandQueueInfo info) {
	return QueryCmdQueue(name.c_str(), info);
}

int stdfuncallconv ClearCmdQueue(const char* name) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	list<MinecraftCommandInfo>::iterator queueiter;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if (iter->QueueName == name) {
			for (queueiter = iter->queue.begin(); queueiter != iter->queue.end(); queueiter++) iter->queue.erase(queueiter);
		}
	}
	return 0;
}
int stdfuncallconv ClearCmdQueue(string name) {
	return ClearCmdQueue(name.c_str());
}

int stdfuncallconv SetCmdQueue(pMinecraftCommandQueueInfo newInfo, pMinecraftCommandQueueInfo oldInfo) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if ((*iter) == *oldInfo) {
			(*iter) = *newInfo;
		}
	}
	return 0;
}

#pragma endregion

#pragma region cmd

//指令操作
int stdfuncallconv NewCmdFront(pMinecraftCommandQueueInfo queue, pMinecraftCommandInfo cmdinfo) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if ((*iter) == *oldInfo) {
			iter->queue.push_front(cmdinfo);
		}
	}
	return 0;
}

int stdfuncallconv NewCmdBack(pMinecraftCommandQueueInfo queue, pMinecraftCommandInfo cmdinfo) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if ((*iter) == *oldInfo) {
			iter->queue.push_back(cmdinfo);
		}
	}
	return 0;
}

int stdfuncallconv DeleteCmd(pMinecraftCommandQueueInfo queue, pMinecraftCommandInfo cmdinfo) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	list<MinecraftCommandInfo>::iterator cmditer;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if ((*iter) == *queue) {
			for (cmditer = iter->queue.begin(); cmditer != iter->queue.end(); cmditer++)
			{
				if ((*cmditer) == *cmdinfo) {
					iter->queue.erase(cmditer);
				}
			}
		}
	}
	return 0;
}
int stdfuncallconv DeleteCmd(pMinecraftCommandQueueInfo queue, const char* cmd) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	list<MinecraftCommandInfo>::iterator cmditer;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if ((*iter) == *queue) {
			for (cmditer = iter->queue.begin(); cmditer != iter->queue.end(); cmditer++)
			{
				if (cmditer->cmd == cmd) {
					iter->queue.erase(cmditer);
				}
			}
		}
	}
	return 0;
}
int stdfuncallconv DeleteCmd(pMinecraftCommandQueueInfo queue, string cmd) {
	return DeleteCmd(queue, cmd.c_str());
}

int stdfuncallconv QueryCmd(pMinecraftCommandQueueInfo queue, pMinecraftCommandInfo cmdinfo, const char* cmd) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	list<MinecraftCommandInfo>::iterator cmditer;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if ((*iter) == *queue) {
			for (cmditer = iter->queue.begin(); cmditer != iter->queue.end(); cmditer++)
			{
				if (cmditer->cmd == cmd) {
					*cmdinfo = *cmditer;
				}
			}
		}
	}
	return 0;
}
int stdfuncallconv QueryCmd(pMinecraftCommandQueueInfo queue, pMinecraftCommandInfo cmdinfo, string cmd) {
	return QueryCmd(queue, cmdinfo, cmd.c_str());
}

int stdfuncallconv SetCmd(pMinecraftCommandQueueInfo queue, pMinecraftCommandInfo newInfo, pMinecraftCommandInfo oldInfo) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	list<MinecraftCommandInfo>::iterator cmditer;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if ((*iter) == *queue) {
			for (cmditer = iter->queue.begin(); cmditer != iter->queue.end(); cmditer++)
			{
				if ((*cmditer) == *oldInfo) {
					*cmditer = *newInfo;
				}
			}
		}
	}
	return 0;
}

MinecraftCommandInfo stdfuncallconv FirstCmd(pMinecraftCommandQueueInfo queue) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if ((*iter) == *oldInfo) {
			return *(iter->queue.begin());
		}
	}
	return 0;
}

MinecraftCommandInfo stdfuncallconv LastCmd(pMinecraftCommandQueueInfo queue) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if ((*iter) == *oldInfo) {
			return *(iter->queue.end());
		}
	}
	return 0;
}

#pragma endregion

//执行
int stdfuncallconv CreateExecThread() {
	thread ExecThread(ExecCmds);
	ExecThread.detach();
	return 0;
}
int stdfuncallconv ExecCmds() {
	list<MinecraftCommandQueueInfo>::iterator iter;
	list<MinecraftCommandInfo>::iterator cmditer;
	int queuepl = CMDQUEUE_PL_HIGHEST;
	int cmdpl = CMD_PL_HIGHEST;
	while (true) {
		if (queuepl == CMDQUEUE_PL_LOWEST) queuepl = CMDQUEUE_PL_HIGHEST;
		if (cmdepl == CMD_PL_LOWEST) cmdpl = CMD_PL_HIGHEST;

		for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
		{
			if (iter->prioritylevel == queuepl) {
				for (cmditer = iter->queue.begin(); cmditer != iter->queue.end(); cmditer++)
				{
					if (cmditer->prioritylevel == cmdpl) {
						WriteToPipe(cmditer->cmd.c_str(), cmditer->cmd.length());
					}
				}
			}
		}
		queuepl--;
		cmdpl--;
	}
	return 0;
}

void DisplayStatus()
{
	list<MinecraftCommandQueueInfo>::iterator iter;
	list<MinecraftCommandInfo>::iterator cmditer;
	out.msg("Minecraft Command Queue Status:");
	out.msg("\tQueues:\tExecute\tPriority Level\tQueueName");
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		string queue;
		queue.append("\t\t");

		if (iter->execute == true) queue.append("true\t");
		else queue.append("false\t");

		switch (iter->prioritylevel)
		{
		case CMDQUEUE_PL_HIGHEST:
			queue.append("Highest\t");
			break;
		case CMDQUEUE_PL_HIGHER:
			queue.append("Higher\t");
			break;
		case CMDQUEUE_PL_NORMAL:
			queue.append("Normal\t");
			break;
		case CMDQUEUE_PL_LOWER:
			queue.append("Lower\t");
			break;
		case CMDQUEUE_PL_LOWEST:
			queue.append("Lowest\t");
			break;
		default:
			break;
		}

		queue.append(iter->QueueName);
		out.msg(queue);
	}
	return;
}
