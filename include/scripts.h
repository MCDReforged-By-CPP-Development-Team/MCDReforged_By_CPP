#pragma once

#include<string>
#include<list>

#include"cfgfile.h"
#include"globaldef.h"

using namespace std;

#define SCHED_FCFS 0
#define SCHED_RR 0

#define SCRSTATE_RUNNING 0
#define SCRSTATE_PAUSE 1
#define SCRSTATE_READY 2
#define SCRSTATE_WAITING 3
#define SCRSTATE_NEW 4
#define SCRSTATE_TERMINATED 5

#define SCRPR_RT 0
#define SCRPR_NORMAL 1
#define SCRPR_LOW 2

class ScriptFile {
public:
	int stdfuncallconv LoadFromDisk(string scrPath);
	ScriptInstance stdfuncallconv CreateIns();
private:
	string scrPath;
	string scrName;
	bool isIllegal;
	bool autoRun;
};

class ScriptInstance {
public:
	int stdfuncallconv SetState(int value);
	int stdfuncallconv GetState();
	int stdfuncallconv SetScrAge(int value);
	int stdfuncallconv SetScrAge();
	int stdfuncallconv GetScrAge();
private:
	int state;
	int priority;
	int age;
};

typedef ScriptInstance* pScriptInstance;

int schedulingAlgorithm = SCHED_RR;

list<ScriptFile> ScrFiles;
list<ScriptInstance> ScrIns_Realtime;
list<ScriptInstance> ScrIns_Normal;
list<ScriptInstance> ScrIns_Low;

int stdfuncallconv ScriptScheduler();
int stdfuncallconv ScriptExecutor();
int stdfuncallconv LoadScript(pScriptInstance scrins);
int stdfuncallconv TerminateScript();