/*
globalsettings.h
��������mcdrcppϵͳ���ü���Ϊ�ı���
*/

#include<string>
#include"cmdsys.h"
#include"cfgfile.h"

using namespace std;

class Globalsettings {
private:
	static int iMsTimerScriptExec;
	static int iExecTimerScriptTimes;

	static bool bLoadCppPlugins;
	static bool bLoadPyPlugins;
	static bool bExecInitScript;
	static bool bReadCppPluginsCfg;
	static bool bReagPyPluginCfg;
	static bool bExecTimerScriptLoop;

	static string strJavaPath;
	static string strServerWorkingDir;
	static string strMinecraftServerFileName;
	static string strCppPluginPath;
	static string strPyPluginPath;
	static string strInitScriptPath;
	static string strTimerScriptPath;
	friend class LoadConfig;
	friend AnalyzeAndExecCommand(string command);
};
