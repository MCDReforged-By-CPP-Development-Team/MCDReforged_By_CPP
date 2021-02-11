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
	MinecraftCommandQueueInfo queue = *info;
	queue.index = MinecraftCommandQueue.size() + 1;
	MinecraftCommandQueue.push_back(queue);
	queue.ExecThread = new thread(ExecCmds, queue.index);
	queue.ExecThread->detach();
	return 0;
}
int stdfuncallconv NewCmdQueue(const char* name) {
	MinecraftCommandQueueInfo info;
	info.execute = true;
	info.QueueName = name;
	info.index = MinecraftCommandQueue.size() + 1;

	MinecraftCommandQueue.push_back(info);
	info.ExecThread = new thread(ExecCmds, info.index);
	info.ExecThread->detach();
	return 0;
}
int stdfuncallconv NewCmdQueue(string name) {
	return NewCmdQueue(name.c_str());
}

int stdfuncallconv DeleteCmdQueue(const char* name) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	int i = 1;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if (iter->QueueName == name) {
			MinecraftCommandQueue.erase(iter);
		}
	}

	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++, i++)
	{
		iter->index = i;
	}
	return 0;
}
int stdfuncallconv DeleteCmdQueue(string name) {
	return DeleteCmdQueue(name.c_str());
}
int stdfuncallconv DeleteCmdQueue(int index) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	int i = 1;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if (iter->index == index) {
			MinecraftCommandQueue.erase(iter);
		}
	}

	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++, i++)
	{
		iter->index = i;
	}

	return 0;
}

int stdfuncallconv QueryCmdQueue(const char* name, pMinecraftCommandQueueInfo info) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if (iter->QueueName == name) {
			*info = *iter;
		}
	}
	return 0;
}
int stdfuncallconv QueryCmdQueue(string name, pMinecraftCommandQueueInfo info) {
	return QueryCmdQueue(name.c_str(), info);
}
int stdfuncallconv QueryCmdQueue(int index, pMinecraftCommandQueueInfo info) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if (iter->index == index) {
			*info = *iter;
		}
	}
	return 0;
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
int stdfuncallconv ClearCmdQueue(int index) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	list<MinecraftCommandInfo>::iterator queueiter;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if (iter->index == index) {
			for (queueiter = iter->queue.begin(); queueiter != iter->queue.end(); queueiter++) iter->queue.erase(queueiter);
		}
	}
	return 0;
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
	list<MinecraftCommandInfo>::iterator cmditer;
	int i = 1;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if ((*iter) == *queue) {
			iter->queue.push_front(*cmdinfo);
		}
	}
	for (cmditer = iter->queue.begin(); cmditer != iter->queue.end(); iter++, i++)
	{
		cmditer->index = i;
	}
	return 0;
}

int stdfuncallconv NewCmdBack(pMinecraftCommandQueueInfo queue, pMinecraftCommandInfo cmdinfo) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	list<MinecraftCommandInfo>::iterator cmditer;
	int i = 1;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if ((*iter) == *queue) {
			iter->queue.push_back(*cmdinfo);
		}
	}
	for (cmditer = iter->queue.begin(); cmditer != iter->queue.end(); iter++, i++)
	{
		cmditer->index = i;
	}
	return 0;
}

int stdfuncallconv DeleteCmd(pMinecraftCommandQueueInfo queue, pMinecraftCommandInfo cmdinfo) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	list<MinecraftCommandInfo>::iterator cmditer;
	int i = 1;
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
	for (cmditer = iter->queue.begin(); cmditer != iter->queue.end(); iter++, i++)
	{
		cmditer->index = i;
	}
	return 0;
}
int stdfuncallconv DeleteCmd(pMinecraftCommandQueueInfo queue, const char* cmd) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	list<MinecraftCommandInfo>::iterator cmditer;
	int i = 1;
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
	for (cmditer = iter->queue.begin(); cmditer != iter->queue.end(); iter++, i++)
	{
		cmditer->index = i;
	}
	return 0;
}
int stdfuncallconv DeleteCmd(pMinecraftCommandQueueInfo queue, string cmd) {
	return DeleteCmd(queue, cmd.c_str());
}
int stdfuncallconv DeleteCmd(pMinecraftCommandQueueInfo queue, int index) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	list<MinecraftCommandInfo>::iterator cmditer;
	int i = 1;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if ((*iter) == *queue) {
			for (cmditer = iter->queue.begin(); cmditer != iter->queue.end(); cmditer++)
			{
				if (cmditer->index == index) {
					iter->queue.erase(cmditer);
				}
			}
		}
	}
	for (cmditer = iter->queue.begin(); cmditer != iter->queue.end(); iter++, i++)
	{
		cmditer->index = i;
	}
	return 0;
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
int stdfuncallconv QueryCmd(pMinecraftCommandQueueInfo queue, pMinecraftCommandInfo cmdinfo, int index) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	list<MinecraftCommandInfo>::iterator cmditer;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if ((*iter) == *queue) {
			for (cmditer = iter->queue.begin(); cmditer != iter->queue.end(); cmditer++)
			{
				if (cmditer->index == index) {
					*cmdinfo = *cmditer;
				}
			}
		}
	}
	return 0;
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
		if ((*iter) == *queue) {
			return *(iter->queue.begin());
		}
	}
}

MinecraftCommandInfo stdfuncallconv LastCmd(pMinecraftCommandQueueInfo queue) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if ((*iter) == *queue) {
			return *(iter->queue.end());
		}
	}
}

#pragma endregion

//执行
int stdfuncallconv ExecCmds(list<MinecraftCommandQueueInfo>::iterator queueiter) {
	list<MinecraftCommandInfo>::iterator cmditer;
	while (true) {
		if (queueiter->execute == true) {
			for (cmditer = queueiter->queue.begin(); cmditer != queueiter->queue.end(); cmditer++) {
				if (cmditer->execute == true) {
					WriteToPipe(cmditer->cmd.c_str(), cmditer->cmd.length());
				}
			}
		}
	}
	return 0;
}

void DisplayStatus()
{
	list<MinecraftCommandQueueInfo>::iterator iter;
	list<MinecraftCommandInfo>::iterator cmditer;
	cmdout.msg("Minecraft Command Queue Status:");
	cmdout.msg("\tQueues:\tExecute\tIndex\tQueueName");
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		string queue;
		queue.append("\t\t");

		if (iter->execute == true) queue.append("true\t");
		else queue.append("false\t");

		queue.append(iter->QueueName);
		cmdout.msg(queue);
	}
	return;
}
