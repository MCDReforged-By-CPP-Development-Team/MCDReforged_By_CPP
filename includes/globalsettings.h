/*
globalsettings.h
包含描述mcdrcpp系统设置及行为的变量
*/

#include<string>

using namespace std;

namespace Globalsettings {
	static int iMsTimerScriptExec;
	static int iExecTimerScriptTimes;
	static int iParserType;

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
	static string strMinecraftServerStartupCommandLine;
	static string strCppPluginPath;
	static string strPyPluginPath;
	static string strInitScriptPath;
	static string strTimerScriptPath;
};
