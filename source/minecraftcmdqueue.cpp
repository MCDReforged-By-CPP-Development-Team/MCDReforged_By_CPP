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

int stdfuncallconv QueryCmdQueue(const char* name, pMinecraftCommandInfo info) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if (iter->QueueName == name) {
			info = iter;
		}
	}
	return 0;
}
int stdfuncallconv QueryCmdQueue(string name, pMinecraftCommandInfo info) {
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
}

int stdfuncallconv NewCmdBack(pMinecraftCommandQueueInfo queue, pMinecraftCommandInfo cmdinfo) {
	list<MinecraftCommandQueueInfo>::iterator iter;
	for (iter = MinecraftCommandQueue.begin(); iter != MinecraftCommandQueue.end(); iter++)
	{
		if ((*iter) == *oldInfo) {
			iter->queue.push_back(cmdinfo);
		}
	}
}

int stdfuncallconv DeleteCmd(pMinecraftCommandQueueInfo queue, pMinecraftCommandInfo cmdinfo) {

}
int stdfuncallconv DeleteCmd(pMinecraftCommandQueueInfo queue, const char* cmd) {

}
int stdfuncallconv DeleteCmd(pMinecraftCommandQueueInfo queue, string cmd) {
	return DeleteCmd(queue, cmd.c_str());
}

int stdfuncallconv QueryCmd(pMinecraftCommandQueueInfo queue, pMinecraftCommandInfo cmdinfo, const char* cmd) {

}
int stdfuncallconv QueryCmd(pMinecraftCommandQueueInfo queue, pMinecraftCommandInfo cmdinfo, string cmd) {
	return QueryCmd(queue, cmdinfo, cmd.c_str());
}

int stdfuncallconv SetCmd(pMinecraftCommandInfo newInfo, pMinecraftCommandInfo oldInfo) {

}

MinecraftCommandInfo stdfuncallconv FirstCmd(pMinecraftCommandQueueInfo queue) {
	
}

MinecraftCommandInfo stdfuncallconv LastCmd(pMinecraftCommandQueueInfo queue) {

}

#pragma endregion

//执行
int stdfuncallconv CreateExecThread() {

}
int stdfuncallconv ExecCmds() {

}