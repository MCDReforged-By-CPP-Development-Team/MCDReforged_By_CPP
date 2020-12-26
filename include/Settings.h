#pragma once

#include<string>
#include<Windows.h>
#include"common.h"
#include"serverparser.h"
#include"debugprint.h"

#pragma region Macros
#define parsertype 0
#define loadcppplugins 1
#define loadpyplugins 2
#define execinitscr 3
#define exectimerscr 4
#define readcpppluginscfg 5
#define readpypluginscfg 6
#define enablemccmdqueue 7
#define javapath 8
#define serverdir 9
#define servername 10
#define cpppluginpath 11
#define pypluginpath 12
#define scrpath 13
#define insprefix 14
#define logpath 15
#define lang 16
#pragma endregion

class _set {
public:
	int iParserType;
	int iLangType;

	bool bLoadCppPlugins;
	bool bLoadPyPlugins;
	bool bExecInitScript;
	bool bExecTimerScript;
	bool bReadCppPluginsCfg;
	bool bReadPyPluginsCfg;
	bool bEnableMinecraftCommandQueue;

	string strJavaPath;
	string strServerWorkingDir;
	string strMinecraftServerStartupCommandLine;
	string strCppPluginPath;
	string strPyPluginPath;
	string strScriptPath;
	string strInstructionPrefix;
	string strLogFilePath;
};
static _set _set_;
int stdfuncallconv GetInt(int set);
bool stdfuncallconv GetBool(int set);
string stdfuncallconv GetString(int set);
int stdfuncallconv SetInt(int set, int value);
bool stdfuncallconv SetBool(int set, bool value);
string stdfuncallconv SetString(int set, string value);