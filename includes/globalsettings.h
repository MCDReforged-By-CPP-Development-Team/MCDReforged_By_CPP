/*
globalsettings.h
包含描述mcdrcpp系统设置及行为的变量
*/

#include<string>
#include"cmdsys.h"

using namespace std;

class Globalsettings {
private:
	static int iMsTimerScriptExec;
	static int iExecTimerScriptTimes;

	static bool bLoadCppPlugins;
	static bool bLoadPyPlugins;
	static bool bExecInitScript;
	static bool bExecTimerScript;
	static bool bReadCppPluginsCfg;
	static bool bReagPyPluginCfg;
	static bool bExecTimerScriptLoop;
	static bool bEnableMinecraftCommandQueue;

	static string strJavaPath;
	static string strServerWorkingDir;
	static string strMinecraftServerFileName;
	static string strCppPluginPath;
	static string strPyPluginPath;
	static string strInitScriptPath;
	static string strTimerScriptPath;
	friend class LoadConfig;
	friend int AnalyzeAndExecCommand(string command);
};
