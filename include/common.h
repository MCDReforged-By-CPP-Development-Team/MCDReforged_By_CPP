/*
common.h by noFe
所有程序的全局定义放进来 awa
*/
#pragma once

#define stdfuncallconv _fastcall	//全部函数统一使用_fastcall调用约定吧 awa(踹开_stdcall和_cdecl
#define MCDRCPP_VER "0.3.5"
#define MCDRCPP_DEV_STATUS "INDEV"  //INDEV/PREVIEW/RELEASE
#define MCDRCPP_RELEASES "https://github.com/MCDReforged-By-CPP-Development-Team/MCDReforged_By_CPP/releases"   //版本发布页
#define MCDRCPP_GITHUBPAGE "https://github.com/MCDReforged-By-CPP-Development-Team/MCDReforged_By_CPP/" //项目主页(GitHub)
#define MCDRCPP_ISSTABLE false //是否为稳定版
#define DEBUG_FUNC_ENABLE   //正式版的时候把这个宏删掉 awa
#define HINTMSG "Some English setences in this program might follow Chinese grammar rules \n which will make it is hard to understand."

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
        "\t<Instructionprefix>!!mcdr </Instructionprefix>\r\n"\
        "\t<LogFilePath>log</LogFilePath>\r\n"\
        "\t<ScriptPath>script</ScriptPath>\r\n"\
        "\t<Language>en_US</Language> <--en_US/zh_CN-->\r\n"\
        "</MCDReforgedByCppConfig>\r\n";

#define CFGFILENAME "mcdrcppconfig.xml"

#define LANG_EN_US 0
#define LANG_ZH_CN 1

#define SETTOCFG_B(name, objname, value) TiXmlElement* p##objname = new TiXmlElement(name);\
if (NULL == p##objname)\
{\
    return false;\
}\
if (Set.GetBool(value) == true) { string strValue = "true"; }\
else { string strValue = "false"; }\
pRootEle->LinkEndChild(p##objname);\
TiXmlText* p##objname##Value = new TiXmlText(strValue.c_str());\
p##objname->LinkEndChild(p##objname)
#define SETTOCFG_S(name, objname, value) TiXmlElement* p##objname = new TiXmlElement(name);\
if (NULL == p##objname)\
{\
    return false;\
}\
pRootEle->LinkEndChild(p##objname);\
TiXmlText* p##objname##Value = new TiXmlText(Set.GetString(value).c_str());\
p##objname->LinkEndChild(p##objname)