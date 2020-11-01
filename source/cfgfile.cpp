#include"cfgfile.h"

using namespace std;

bool LoadConfig::ConfigFileExisting() {
    char strCfgPath[MAX_PATH];
    GetModuleFileName(NULL, strCfgPath, MAX_PATH);
    (strrchr(strCfgPath, '\\'))[1] = 0;
    strcat_s(strCfgPath, CFGFILENAME); //获取mcdrcpp配置文件路径

    HANDLE hFile = ::CreateFile(
        strCfgPath,
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        0);
    if (hFile == INVALID_HANDLE_VALUE) return false;    //判断mcdrcpp配置文件是否存在
    CloseHandle(hFile);
    return true;
}

int LoadConfig::LoadConfigFile() {
    DebugPrint("Enter LoadConfigFile()!");
    DebugPrint(ConfigFileExisting());
    if (ConfigFileExisting()) {
        return ReadCfgFile();
        return 0;
    }
    else {
        CreateCfgFile();
        
        return ReadCfgFile();
        return -1;
    }
}

int LoadConfig::Default()
{
    iParserType = VANILLA_PARSER_CODE;

    bLoadCppPlugins = true;
    bLoadPyPlugins = true;
    bExecInitScript = true;
    bExecTimerScript = true;
    bReadCppPluginsCfg = true;
    bReadPyPluginsCfg = true;
    bExecTimerScriptLoop = true;
    bEnableMinecraftCommandQueue = true;

    strJavaPath = "";
    strServerWorkingDir = "server";
    strMinecraftServerStartupCommandLine = "-nogui";
    strCppPluginPath = "plugins";
    strPyPluginPath = "plugins";
    strInitScriptPath = "script";
    strTimerScriptPath = "script";
    strInstructionPrefix = "!!mcdr";
    strLogFilePath = "log";
    return 0;
}

int LoadConfig::CreateCfgFile() {
    char strCfgPath[MAX_PATH];
    char strCfgFile[] = COMMOM_CFG;
    DWORD dwWriteBytes;

    HANDLE hFile = ::CreateFile(
        CFGFILENAME,
        GENERIC_WRITE|GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        0);
    if (hFile == INVALID_HANDLE_VALUE) return false;    //判断mcdrcpp配置文件是否存在
    WriteFile(hFile, strCfgFile, sizeof(strCfgFile), &dwWriteBytes, NULL);
    CloseHandle(hFile);
    return 0;
}

int LoadConfig::ReadCfgFile() {
    DebugPrint("Enter ReadCfgFile()!");
    TiXmlDocument Doc(CFGFILENAME);

    bool bret = Doc.LoadFile(TIXML_ENCODING_UTF8);
    string tinyxmlerror = ("ErrorID:" + Doc.ErrorId());
    tinyxmlerror += "ErrorDesc:";
    tinyxmlerror += Doc.ErrorDesc();
    if (!bret) {
        DebugPrint("Doc.LoadFile() failed.");
        DebugPrint(tinyxmlerror);
        return -1;
    }
    DebugPrint("Load Config File Successful.");
    TiXmlElement* pRootEle = Doc.RootElement();
    if (pRootEle == NULL) {
        DebugPrint("Doc.RootElement(); failed.");
        return -1;
    }
    DebugPrint("Get XML Root Element Successful.");

    TiXmlElement* pElem = NULL;

    GetNodePointerByName(pRootEle, (string)"LoadCppPlugins", pElem);
    if (pElem == NULL) return -1;
    bLoadCppPlugins = StringToBool(pElem->GetText());
    DebugPrint("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"LoadPythonPlugins", pElem);
    if (pElem == NULL) return -1;
    bLoadPyPlugins = StringToBool(pElem->GetText());
    DebugPrint("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"LoadCppPluginsConfig", pElem);
    if (pElem == NULL) return -1;
    bReadCppPluginsCfg = StringToBool(pElem->GetText());
    DebugPrint("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"LoadPythonPluginsConfig", pElem);
    if (pElem == NULL) return -1;
    bReadPyPluginsCfg = StringToBool(pElem->GetText());
    DebugPrint("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"CppPluginsDir", pElem);
    if (pElem == NULL) return -1;
    strCppPluginPath = pElem->GetText();
    DebugPrint("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"PythonPluginsDir", pElem);
    if (pElem == NULL) return -1;
    strPyPluginPath = pElem->GetText();
    DebugPrint("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"ExecInitScript", pElem);
    if (pElem == NULL) return -1;
    bExecInitScript = StringToBool(pElem->GetText());
    DebugPrint("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"LoadCppPlugins", pElem);
    if (pElem == NULL) return -1;
    bExecTimerScript = StringToBool(pElem->GetText());
    DebugPrint("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"ServerDir", pElem);
    if (pElem == NULL) return -1;
    strServerWorkingDir = pElem->GetText();
    DebugPrint("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"ServerStartupCommand", pElem);
    if (pElem == NULL) return -1;
    strMinecraftServerStartupCommandLine = pElem->GetText();
    DebugPrint("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"JavaPath", pElem);
    if (pElem == NULL) return -1;
    strJavaPath = pElem->GetText();
    DebugPrint("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"EnableMinecraftCommandQueue", pElem);
    if (pElem == NULL) return -1;
    bEnableMinecraftCommandQueue = StringToBool(pElem->GetText());
    DebugPrint("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"ServerParser", pElem);
    if (pElem == NULL) return -1;
    iParserType = StringToParserCode(pElem->GetText());
    DebugPrint("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"Instructionprefix", pElem);
    if (pElem == NULL) return -1;
    strInstructionPrefix = pElem->GetText();
    DebugPrint("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"LogFilePath", pElem);
    if (pElem == NULL) return -1;
    strLogFilePath = pElem->GetText();
    DebugPrint("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"InitScriptPath", pElem);
    if (pElem == NULL) return -1;
    strInitScriptPath = pElem->GetText();
    DebugPrint("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"TimerScriptPath", pElem);
    if (pElem == NULL) return -1;
    strTimerScriptPath = pElem->GetText();
    DebugPrint("Read Config Successful.");


    DebugPrint("Exiting ReadCfgFile()");
    return 0;
}

bool LoadConfig::GetNodePointerByName(TiXmlElement* pRootEle, std::string& strNodeName, TiXmlElement*& Node)    //此函数来自于CSDN 链接:https://blog.csdn.net/masikkk/article/details/14191933?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.add_param_isCf&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.add_param_isCf
{
    DebugPrint("GetNodePointerByName()" + strNodeName);
    if (strNodeName == pRootEle->Value())
    {
        Node = pRootEle;
        return true;
    }
    TiXmlElement* pEle = pRootEle;
    for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement())
    {
        if (GetNodePointerByName(pEle, strNodeName, Node))
            return true;
    }
    return false;
}

bool LoadConfig::StringToBool(string Temp) {
    if (Temp == "true" || Temp == "TRUE" || Temp == "True") return true;
    else if (Temp == "false" || Temp == "FALSE" || Temp == "False") return false;
    return false;
}

int LoadConfig::StringToParserCode(string parserName) {
    if (parserName == "VanillaParser") {
        return VANILLA_PARSER_CODE;
    }

    if (parserName == "BukkitParser") {
        return BUKKIT_PARSER_CODE;
    }

    if (parserName == "Bukkit14Parser") {
        return BUKKIT_14_PARSER_CODE;
    }

    if (parserName == "BungeeCordParser") {
        return BUNGEECORD_PARSER_CODE;
    }

    if (parserName == "CatServerParser") {
        return CAT_SERVER_PARSER_CODE;
    }

    if (parserName == "WaterfallParser") {
        return WATERFALL_PARSER_CODE;
    }
}
#ifdef DEBUG_FUNC_ENABLE
int stdfuncallconv PrintAttr()
{
    DebugPrint(iParserType);

    DebugPrint(bLoadCppPlugins);
    DebugPrint(bLoadPyPlugins);
    DebugPrint(bExecInitScript);
    DebugPrint(bExecTimerScript);
    DebugPrint(bReadCppPluginsCfg);
    DebugPrint(bReadPyPluginsCfg);
    DebugPrint(bExecTimerScriptLoop);
    DebugPrint(bEnableMinecraftCommandQueue);

    DebugPrint(strJavaPath);
    DebugPrint(strServerWorkingDir);
    DebugPrint(strMinecraftServerStartupCommandLine);
    DebugPrint(strCppPluginPath);
    DebugPrint(strPyPluginPath);
    DebugPrint(strInitScriptPath);
    DebugPrint(strTimerScriptPath);
    DebugPrint(strInstructionPrefix);
    DebugPrint(strLogFilePath);
    return 0;
}
#endif
