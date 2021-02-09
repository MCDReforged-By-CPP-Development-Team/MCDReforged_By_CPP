#pragma once

#include<list>
#include<map>
#include<string>
#include<thread>

#include"common.h"
#include"debugprint.h"
#include"redirectstdio.h"
#include"logsys.h"

OutputInterface out;

using namespace std;

#define CMD_PL_HIGHEST 2
#define CMD_PL_HIGHER 1
#define CMD_PL_NORMAL 0
#define CMD_PL_LOWER -1;
#define CMD_PL_LOWEST -2;

#define CMDQUEUE_PL_HIGHEST 2
#define CMDQUEUE_PL_HIGHER 1
#define CMDQUEUE_PL_NORMAL 0
#define CMDQUEUE_PL_LOWER -1;
#define CMDQUEUE_PL_LOWEST -2;

struct MinecraftCommandInfo {
	int prioritylevel;
	int cate;
	bool execute;
	string cmd;

	bool operator==(MinecraftCommandInfo b) const {
		return this->prioritylevel == b.prioritylevel
			&& this->cate == b.cate
			&& this->execute == b.execute
			&& this->cmd == b.cmd;
	}

	void operator=(MinecraftCommandInfo b) {
		this->prioritylevel = b.prioritylevel;
		this->cate = b.cate;
		this->execute = b.execute;
		this->cmd = b.cmd;
	}
};

struct MinecraftCommandQueueInfo {
	string QueueName;
	bool execute;
	int prioritylevel;
	list<MinecraftCommandInfo> queue;

	bool operator==(MinecraftCommandQueueInfo b) const {
		return this->prioritylevel == b.prioritylevel
			&& this->QueueName == b.QueueName
			&& this->execute == b.execute;
	}

	void operator=(MinecraftCommandQueueInfo b) {
		this->prioritylevel = b.prioritylevel;
		this->QueueName = b.QueueName;
		this->execute = b.execute;
		this->queue = b.queue;
	}
};

typedef MinecraftCommandInfo* pMinecraftCommandInfo;
typedef MinecraftCommandQueueInfo* pMinecraftCommandQueueInfo;

//队列操作
int stdfuncallconv NewCmdQueue(pMinecraftCommandQueueInfo info);
int stdfuncallconv NewCmdQueue(const char* name);
int stdfuncallconv NewCmdQueue(string name);

int stdfuncallconv DeleteCmdQueue(const char* name);
int stdfuncallconv DeleteCmdQueue(string name);

int stdfuncallconv QueryCmdQueue(const char* name, pMinecraftCommandQueueInfo info);
int stdfuncallconv QueryCmdQueue(string name, pMinecraftCommandQueueInfo info);

int stdfuncallconv ClearCmdQueue(const char* name);
int stdfuncallconv ClearCmdQueue(string name);

int stdfuncallconv SetCmdQueue(pMinecraftCommandQueueInfo newInfo, pMinecraftCommandQueueInfo oldInfo);

//指令操作
int stdfuncallconv NewCmdFront(pMinecraftCommandQueueInfo queue, pMinecraftCommandInfo cmdinfo);

int stdfuncallconv NewCmdBack(pMinecraftCommandQueueInfo queue, pMinecraftCommandInfo cmdinfo);

int stdfuncallconv DeleteCmd(pMinecraftCommandQueueInfo queue, pMinecraftCommandInfo cmdinfo);
int stdfuncallconv DeleteCmd(pMinecraftCommandQueueInfo queue, const char* cmd);
int stdfuncallconv DeleteCmd(pMinecraftCommandQueueInfo queue, string cmd);

int stdfuncallconv QueryCmd(pMinecraftCommandQueueInfo queue, pMinecraftCommandInfo cmdinfo, const char* cmd);
int stdfuncallconv QueryCmd(pMinecraftCommandQueueInfo queue, pMinecraftCommandInfo cmdinfo, string cmd);

int stdfuncallconv SetCmd(pMinecraftCommandQueueInfo queue, pMinecraftCommandInfo newInfo, pMinecraftCommandInfo oldInfo);

MinecraftCommandInfo stdfuncallconv FirstCmd(pMinecraftCommandQueueInfo queue);

MinecraftCommandInfo stdfuncallconv LastCmd(pMinecraftCommandQueueInfo queue);

//执行
int stdfuncallconv CreateExecThread();
int stdfuncallconv ExecCmds();
void stdfuncallconv DisplayStatus();