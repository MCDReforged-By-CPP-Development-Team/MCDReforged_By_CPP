#include"globalsettings.h"

int iMsTimerScriptExec = 10;
int iExecTimerScriptTimes = 0;
int iParserType = VANILLA_PARSER_CODE;

bool bLoadCppPlugins = true;
bool bLoadPyPlugins = true;
bool bExecInitScript = true;
bool bExecTimerScript = true;
bool bReadCppPluginsCfg = true;
bool bReagPyPluginCfg = true;
bool bExecTimerScriptLoop = true;
bool bEnableMinecraftCommandQueue = true;

std::string strJavaPath = "";
std::string strServerWorkingDir = "";
std::string strMinecraftServerStartupCommandLine = "";
std::string strCppPluginPath = "";
std::string strPyPluginPath = "";
std::string strInitScriptPath = "";
std::string strTimerScriptPath = "";

/*
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
*/

template<class attrtype>
attrtype _Globalsettings::SetAttributes(int attributes, attrtype setvalue) {
	switch (attributes)
	{
	ATTR_MSTIMERSCRIPTEXEC:
		break;
	ATTR_EXECTIMERSCRIPTTIMES:
		break;
	ATTR_PARSERTYPE:
		break;

	ATTR_LOADCPPPLUGINS:
		break;
	ATTR_LOADPYPLUGINS:
		break;
	ATTR_EXECINITSCRIPT:
		break;
	ATTR_EXECTIMERSCRIPT:
		break;
	ATTR_READCPPPLUGINCFG:
		break;
	ATTR_READPYPLUGINCFG:
		break;
	ATTR_EXECTIMERSCRIPTLOOP:
		break;
	ATTR_ENABLEMINECRAFTCOMMANDQUEUE:
		break;

	ATTR_JAVAPATH:
		break;
	ATTR_SERVERWORKINGDIR:
		break;
	ATTR_MINECRAFTSERVERSTARTUPCOMMANDLINE:
		break;
	ATTR_CPPPLUGINPATH:
		break;
	ATTR_PYPLUGINPATH:
		break;
	ATTR_INITSCRIPTPATH:
		break;
	ATTR_TIMERSCRIPTPATH:
		break;
	
	default:
		break;
	}
}