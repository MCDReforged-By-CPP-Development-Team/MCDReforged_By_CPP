/*
cfgfile.h
包含读取配置文件的类及成员函数声明
*/
#pragma once

#include<string>
#include<Windows.h>
#include"common.h"
#include"logsys.h"
#include"serverparser.h"
#include"debugprint.h"
#include"tinyxml2-8.0.0/tinystr.h"  
#include"tinyxml2-8.0.0/tinyxml.h"

using namespace std;

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

class Settings {
private:
   /*
    static int iParserType;
    static int iLangType;
    
    static bool bLoadCppPlugins;
    static bool bLoadPyPlugins;
    static bool bExecInitScript;
    static bool bExecTimerScript;
    static bool bReadCppPluginsCfg;
    static bool bReadPyPluginsCfg;
    static bool bEnableMinecraftCommandQueue;

    static string strJavaPath;
    static string strServerWorkingDir;
    static string strMinecraftServerStartupCommandLine;
    static string strCppPluginPath;
    static string strPyPluginPath;
    static string strScriptPath;
    static string strInstructionPrefix;
    static string strLogFilePath;
    */
public:
    int stdfuncallconv GetInt(int set);
    bool stdfuncallconv GetBool(int set);
    string stdfuncallconv GetString(int set);
    int stdfuncallconv SetInt(int set, int value);
    bool stdfuncallconv SetBool(int set, bool value);
    string stdfuncallconv SetString(int set, string value);
};

class LoadConfig {
private:
    int stdfuncallconv ReadCfgFile();
	int stdfuncallconv CreateCfgFile();
	bool stdfuncallconv ConfigFileExisting();
	bool stdfuncallconv StringToBool(string Temp);
	bool stdfuncallconv GetNodePointerByName(TiXmlElement* pRootEle, const char* strNodeName, TiXmlElement*& Node);
	int stdfuncallconv StringToParserCode(string parserName);
public:
	static int stdfuncallconv LoadConfigFile();
	int stdfuncallconv SettingHelper();
    int stdfuncallconv SetToCfg();
};
