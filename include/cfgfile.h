/*
cfgfile.h
包含读取配置文件的类及成员函数声明
*/
#pragma once

#include<string>
#include<Windows.h>
#include"common.h"
#include"tinyxml2-8.0.0/tinystr.h"  
#include"tinyxml2-8.0.0/tinyxml.h"

using namespace std;

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
#define mcserverstart 10
#define cpppluginpath 11
#define pypluginpath 12
#define scrpath 13
#define insprefix 14
#define logpath 15

class Settings {
private:
    int iParserType;
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
public:
    int stdfuncallconv GetInt(int set);
    bool stdfuncallconv GetBool(int set);
    string stdfuncallconv GetString(int set);
    int stdfuncallconv SetInt(int set, int value);
    bool stdfuncallconv SetBool(int set, bool value);
    string stdfuncallconv SetString(int set, string value);
    Settings();
};

class LoadConfig {
private:
    int stdfuncallconv ReadCfgFile();
	int stdfuncallconv CreateCfgFile();
	bool stdfuncallconv ConfigFileExisting();
	bool stdfuncallconv StringToBool(string Temp);
	bool stdfuncallconv GetNodePointerByName(TiXmlElement* pRootEle, std::string& strNodeName, TiXmlElement*& Node);
	int stdfuncallconv StringToParserCode(string parserName);
public:
	static int LoadConfigFile();
	int Default();
};

extern LoadConfig Cfg;
extern Settings GlobalSettings;