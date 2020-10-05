/*
globalsettings.h
包含描述mcdrcpp系统设置及行为的变量
*/
#pragma once

#include<string>
#include"serverparser.h"

#define ATTR_MSTIMERSCRIPTEXEC 0
#define ATTR_EXECTIMERSCRIPTTIMES 1
#define ATTR_PARSERTYPE 2

#define ATTR_LOADCPPPLUGINS 3
#define ATTR_LOADPYPLUGINS 4
#define ATTR_EXECINITSCRIPT 5
#define ATTR_EXECTIMERSCRIPT 6
#define ATTR_READCPPPLUGINCFG 7
#define ATTR_READPYPLUGINCFG 8
#define ATTR_EXECTIMERSCRIPTLOOP 9
#define ATTR_ENABLEMINECRAFTCOMMANDQUEUE 10

#define ATTR_JAVAPATH 11
#define ATTR_SERVERWORKINGDIR 12
#define ATTR_MINECRAFTSERVERSTARTUPCOMMANDLINE 13
#define ATTR_CPPPLUGINPATH 14
#define ATTR_PYPLUGINPATH 15
#define ATTR_INITSCRIPTPATH 16
#define ATTR_TIMERSCRIPTPATH 17

class _Globalsettings {
private:
	volatile static int iMsTimerScriptExec;
	volatile static int iExecTimerScriptTimes;
	volatile static int iParserType;

	volatile static bool bLoadCppPlugins;
	volatile static bool bLoadPyPlugins;
	volatile static bool bExecInitScript;
	volatile static bool bExecTimerScript;
	volatile static bool bReadCppPluginsCfg;
	volatile static bool bReagPyPluginCfg;
	volatile static bool bExecTimerScriptLoop;
	volatile static bool bEnableMinecraftCommandQueue;

	static std::string strJavaPath;
	static std::string strServerWorkingDir;
	static std::string strMinecraftServerStartupCommandLine;
	static std::string strCppPluginPath;
	static std::string strPyPluginPath;
	static std::string strInitScriptPath;
	static std::string strTimerScriptPath;
public:
	template<class attrtype>
	attrtype SetAttributes(int attributes, attrtype setvalue);
};

volatile static _Globalsettings Globalsettings;

