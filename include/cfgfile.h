/*
cfgfile.h
包含读取配置文件的类及成员函数声明
*/
#pragma once

#include<string>
#include<Windows.h>
#include<strstream>
#include<string>

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

#pragma region Declares
extern int iParserType;
extern int iLangType;
extern bool bLoadCppPlugins;
extern bool bLoadPyPlugins;
extern bool bExecInitScript;
extern bool bExecTimerScript;
extern bool bReadCppPluginsCfg;
extern bool bReadPyPluginsCfg;
extern bool bEnableMinecraftCommandQueue;
extern string strJavaPath;
extern string strServerWorkingDir;
extern string strMinecraftServerStartupCommandLine;
extern string strCppPluginPath;
extern string strPyPluginPath;
extern string strScriptPath;
extern string strInstructionPrefix;
extern string strLogFilePath;
#pragma endregion

#pragma region Macros2
#define COMMOM_CFG "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"\
        "<MCDReforgedByCppConfig>\r\n"\
        "\t<LoadCppPlugins>true</LoadCppPlugins>\r\n"\
        "\t<LoadPythonPlugins>true</LoadPythonPlugins>\r\n"\
        "\t<LoadCppPluginsConfig>true</LoadCppPluginsConfig>\r\n"\
        "\t<LoadPythonPluginsConfig>true</LoadPythonPluginsConfig>\r\n"\
        "\t<CppPluginsDir>plugins</CppPluginsDir>\r\n"\
        "\t<PythonPluginsDir>plugins</PythonPluginsDir>\r\n"\
        "\t<ExecInitScript>true</ExecInitScript>\r\n"\
        "\t<ExecTimerScript>true</ExecTimerScript>\r\n"\
        "\t<ServerDir>server</ServerDir>\r\n"\
        "\t<ServerStartupCommand>server.jar</ServerStartupCommand>\r\n"\
        "\t<JavaPath>init</JavaPath>\r\n"\
        "\t<EnableMinecraftCommandQueue>true</EnableMinecraftCommandQueue>\r\n"\
        "\t<ServerParser>VanillaParser</ServerParser>\r\n"\
        "\t<InstructionPrefix>!!MCDR</InstructionPrefix>\r\n"\
        "\t<LogFilePath>log</LogFilePath>\r\n"\
        "\t<ScriptPath>script</ScriptPath>\r\n"\
        "\t<Language>en_US</Language> <--en_US/zh_CN-->\r\n"\
        "</MCDReforgedByCppConfig>\r\n";

#define CFGFILENAME "mcdrcppconfig.xml"

#define LANG_EN_US 0
#define LANG_ZH_CN 1

#define SETTOCFG_B(name, objname, value) TiXmlElement* p##objname = new TiXmlElement(name);\
if (NULL == p##objname) return false;\
if (Set.GetBool(value) == true) { strValue = "true"; }\
else { strValue = "false"; }\
pRootEle->LinkEndChild(p##objname);\
TiXmlText* p##objname##Value = new TiXmlText(strValue.c_str());\
p##objname->LinkEndChild(p##objname##Value)

#define SETTOCFG_S(name, objname, value) TiXmlElement* p##objname = new TiXmlElement(name);\
if (NULL == p##objname) return false;\
pRootEle->LinkEndChild(p##objname);\
TiXmlText* p##objname##Value = new TiXmlText(Set.GetString(value).c_str());\
p##objname->LinkEndChild(p##objname##Value)

#define stb StringToBool(pElem->GetText())
#define gt pElem->GetText()
#define rettest if (pElem == NULL) {\
    dp("Read Config Failed.");\
    iret = -1;\
    return iret;\
}
#pragma endregion

class Settings {
public:
    int stdfuncallconv GetInt(int set);
    bool stdfuncallconv GetBool(int set);
    string stdfuncallconv GetString(int set);
    void stdfuncallconv SetInt(int set, int value);
    void stdfuncallconv SetBool(int set, bool value);
    void stdfuncallconv SetString(int set, string value);
    void stdfuncallconv SetString(int set, LPSTR value);
    void stdfuncallconv SetString(int set, LPCSTR value);
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
