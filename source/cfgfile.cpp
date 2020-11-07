#include"cfgfile.h"
#include"common.h"
#include"serverparser.h"
#include"debugprint.h"

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
    dp("Enter LoadConfigFile()!");
    dp(Cfg.ConfigFileExisting());
    if (Cfg.ConfigFileExisting()) {
        return Cfg.ReadCfgFile();
        return 0;
    }
    else {
        Cfg.CreateCfgFile();
        
        return Cfg.ReadCfgFile();
        return -1;
    }
}

int LoadConfig::Default()
{
    GlobalSettings.SetInt(parsertype, VANILLA_PARSER_CODE);

    GlobalSettings.SetBool(loadcppplugins, true);
    GlobalSettings.SetBool(loadpyplugins, true);
    GlobalSettings.SetBool(execinitscr, true);
    GlobalSettings.SetBool(exectimerscr, true);
    GlobalSettings.SetBool(readcpppluginscfg, true);
    GlobalSettings.SetBool(readpypluginscfg, true);
    GlobalSettings.SetBool(enablemccmdqueue, true);

    GlobalSettings.SetString(javapath, "");
    GlobalSettings.SetString(serverdir, "server");
    GlobalSettings.SetString(mcserverstart, "server.jar");
    GlobalSettings.SetString(cpppluginpath, "plugins");
    GlobalSettings.SetString(pypluginpath, "plugins");
    GlobalSettings.SetString(scrpath, "script");
    GlobalSettings.SetString(insprefix, "!!mcdr");
    GlobalSettings.SetString(logpath, "log");
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
    dp("Enter ReadCfgFile()!");
    TiXmlDocument Doc(CFGFILENAME);

    bool bret = Doc.LoadFile(TIXML_ENCODING_UTF8);
    string tinyxmlerror = ("ErrorID:" + Doc.ErrorId());
    tinyxmlerror += "ErrorDesc:";
    tinyxmlerror += Doc.ErrorDesc();
    if (!bret) {
        dp("Doc.LoadFile() failed.");
        dp(tinyxmlerror);
        return -1;
    }
    dp("Load Config File Successful.");
    TiXmlElement* pRootEle = Doc.RootElement();
    if (pRootEle == NULL) {
        dp("Doc.RootElement(); failed.");
        return -1;
    }
    dp("Get XML Root Element Successful.");

    TiXmlElement* pElem = NULL;
#define stb StringToBool(pElem->GetText())
#define gt pElem->GetText()
    GetNodePointerByName(pRootEle, (string)"LoadCppPlugins", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetBool(loadcppplugins, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"LoadPythonPlugins", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetBool(loadpyplugins, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"LoadCppPluginsConfig", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetBool(readcpppluginscfg, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"LoadPythonPluginsConfig", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetBool(readpypluginscfg, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"CppPluginsDir", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetBool(cpppluginpath, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"PythonPluginsDir", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetBool(pypluginpath, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"ExecInitScript", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetBool(execinitscr, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"LoadCppPlugins", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetBool(exectimerscr, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"ServerDir", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetString(serverdir, gt);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"ServerStartupCommand", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetString(mcserverstart, gt);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"JavaPath", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetString(javapath, gt);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"EnableMinecraftCommandQueue", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetBool(enablemccmdqueue, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"ServerParser", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetInt(parsertype, StringToParserCode(pElem->GetText()));
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"Instructionprefix", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetString(insprefix, gt);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"LogFilePath", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetString(logpath, gt);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, (string)"ScriptPath", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetString(scrpath, gt);
    dp("Read Config Successful.");

    dp("Exiting ReadCfgFile()");
    return 0;
}

bool LoadConfig::GetNodePointerByName(TiXmlElement* pRootEle, std::string& strNodeName, TiXmlElement*& Node)    //此函数来自于CSDN 链接:https://blog.csdn.net/masikkk/article/details/14191933?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.add_param_isCf&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.add_param_isCf
{
    dp("GetNodePointerByName()" + strNodeName);
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
    return VANILLA_PARSER_CODE;
}

int stdfuncallconv Settings::GetInt(int set)
{
    switch (set) 
    {
    case parsertype:
        return iParserType;
        break;
    default:
        return -1;
        break;
    }
    return 0;
}

bool stdfuncallconv Settings::GetBool(int set)
{
    switch (set)
    {
    case loadcppplugins:
        return bLoadCppPlugins;
        break;
    case loadpyplugins:
        return bLoadPyPlugins;
        break;
    case execinitscr:
        return bExecInitScript;
        break;
    case exectimerscr:
        return bExecTimerScript;
        break;
    case readcpppluginscfg:
        return bReadCppPluginsCfg;
        break;
    case readpypluginscfg:
        return bReadPyPluginsCfg;
        break;
    case enablemccmdqueue:
        return bEnableMinecraftCommandQueue;
        break;
    default:
        break;
    }
    return false;
}

string stdfuncallconv Settings::GetString(int set)
{
    switch (set)
    {
    case javapath:
        return strJavaPath;
        break;
    case serverdir:
        return strServerWorkingDir;
        break;
    case mcserverstart:
        return strMinecraftServerStartupCommandLine;
        break;
    case cpppluginpath:
        return strCppPluginPath;
        break;
    case pypluginpath:
        return strPyPluginPath;
        break;
    case scrpath:
        return strScriptPath;
        break;
    case insprefix:
        return strInstructionPrefix;
        break;
    case logpath:
        return strLogFilePath;
        break;
    default:
        break;
    }
    return "";
}

int stdfuncallconv Settings::SetInt(int set, int value)
{
    switch (set)
    {
    case parsertype:
        iParserType = value;
        break;
    default:
        return -1;
        break;
    }
    return 0;
}

bool stdfuncallconv Settings::SetBool(int set, bool value)
{
    switch (set)
    {
    case loadcppplugins:
        bLoadCppPlugins = value;
        break;
    case loadpyplugins:
        bLoadPyPlugins = value;
        break;
    case execinitscr:
        bExecInitScript = value;
        break;
    case exectimerscr:
        bExecTimerScript = value;
        break;
    case readcpppluginscfg:
        bReadCppPluginsCfg = value;
        break;
    case readpypluginscfg:
        bReadPyPluginsCfg = value;
        break;
    case enablemccmdqueue:
        bEnableMinecraftCommandQueue = value;
        break;
    default:
        break;
    }
    return false;
}

string stdfuncallconv Settings::SetString(int set, string value)
{
    switch (set)
    {
    case javapath:
        strJavaPath = value;
        break;
    case serverdir:
        strServerWorkingDir = value;
        break;
    case mcserverstart:
        strMinecraftServerStartupCommandLine = value;
        break;
    case cpppluginpath:
        strCppPluginPath = value;
        break;
    case pypluginpath:
        strPyPluginPath = value;
        break;
    case scrpath:
        strScriptPath;
        break;
    case insprefix:
        strInstructionPrefix = value;
        break;
    case logpath:
        strLogFilePath = value;
        break;
    default:
        break;
    }
    return "";
}

Settings::Settings()
{
    iParserType = VANILLA_PARSER_CODE;
    bLoadCppPlugins = true;
    bLoadPyPlugins = true;
    bExecInitScript = true;
    bExecTimerScript = true;
    bReadCppPluginsCfg = true;
    bReadPyPluginsCfg = true;
    bEnableMinecraftCommandQueue = true;

    strJavaPath = "";
    strServerWorkingDir = "server";
    strMinecraftServerStartupCommandLine = "server.jar";
    strCppPluginPath = "plugins";
    strPyPluginPath = "plugins";
    strScriptPath = "script";
    strInstructionPrefix = "!!mcdr";
    strLogFilePath = "log";
}
