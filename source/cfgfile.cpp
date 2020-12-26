#include"cfgfile.h"

LoadConfig Cfg;
Settings GlobalSettings;
OutputInterface Out;

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

int stdfuncallconv LoadConfig::SettingHelper()
{
    GlobalSettings.SetInt(lang, LANG_EN_US);
    Out.mlout("Welcome to SettingHelper", "欢迎来到配置文件设置助手");
    Out.mlout("Select Server Type[Vanilla-0][Bukkit(Version<1.14)-1][Bukkit(Version>=1.14)][BungeeCord-3][Cat-4][Waterfall-5]",
              "请选择您的服务器端类型[Vanilla-0][Bukkit(Version<1.14)-1][Bukkit(Version>=1.14)][BungeeCord-3][Cat-4][Waterfall-5]");
    int ivar;
    parser:
    cin >> ivar;
    if (ivar > WATERFALL_PARSER_CODE || ivar < VANILLA_PARSER_CODE)goto parser;
    return 0;
}

int stdfuncallconv LoadConfig::SetToCfg()
{
    dp("Enter SetToCfg()!");
    Settings Set;
    TiXmlDocument* pDoc = new TiXmlDocument;
    if (NULL == pDoc)
    {
        return false;
    }
    TiXmlDeclaration* pDeclaration = new TiXmlDeclaration("1.0", "UTF-8", " ");
    if (NULL == pDeclaration)
    {
        return false;
    }
    pDoc->LinkEndChild(pDeclaration);
    TiXmlElement* pRootEle = new TiXmlElement("MCDReforgedByCppConfig");
    if (NULL == pRootEle)
    {
        return false;
    }
    pDoc->LinkEndChild(pRootEle);
    string strValue;
    /*
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"\
        "<MCDReforgedByCppConfig>\r\n"\
        "\t<LoadCppPlugins>true</LoadCppPlugins>\r\n"\
        "\t<LoadPythonPlugins>true</LoadPythonPlugins>\r\n"\
        "\t<LoadCppPluginsConfig>true</LoadCppPluginsConfig>\r\n"\
        "\t<LoadPythonPluginsConfig>true</LoadPythonPluginsConfig>\r\n"\
        "\t<CppPluginsDir>cppplugins</CppPluginsDir>\r\n"\
        "\t<PythonPluginsDir>pyplugins</PythonPluginsDir>\r\n"\
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
    */
    SETTOCFG_B("LoadCppPlugins", LoadCpp, loadcppplugins);
    SETTOCFG_B("LoadPythonPlugins", LoadPy, loadpyplugins);
    SETTOCFG_B("LoadCppPluginsConfig", LoadCppCfg, readcpppluginscfg);
    SETTOCFG_B("LoadPythonPluginsConfig", LoadPyCfg, readpypluginscfg);
    SETTOCFG_B("ExecInitScript", ExecInitScript, execinitscr);
    SETTOCFG_B("ExecTimerScript", ExecTimerScript, exectimerscr);
    SETTOCFG_B("EnableMinecraftCommandQueue", EnableMinecraftCommandQueue, enablemccmdqueue);

    SETTOCFG_S("CppPluginsDir", CppPluginsDir, cpppluginpath);
    SETTOCFG_S("PythonPluginsDir", PyPluginsDir, pypluginpath);
    SETTOCFG_S("ServerDir", ServerDir, serverdir);
    SETTOCFG_S("ServerStartupCommand", ServerStartupCommand, servername);
    SETTOCFG_S("JavaPath", JavaPath, javapath);
    SETTOCFG_S("InstructionPrefix", InstructionPrefix, insprefix);
    SETTOCFG_S("LogFilePath", LogFilePath, logpath);
    SETTOCFG_S("LogFileScriptPath", ScriptPath, scrpath);
}

int LoadConfig::CreateCfgFile() {
    char strCfgPath[MAX_PATH] = {};
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
    GetNodePointerByName(pRootEle, "LoadCppPlugins", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetBool(loadcppplugins, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "LoadPythonPlugins", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetBool(loadpyplugins, stb);
    dp("Read Config Successful.");  

    GetNodePointerByName(pRootEle, "LoadCppPluginsConfig", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetBool(readcpppluginscfg, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "LoadPythonPluginsConfig", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetBool(readpypluginscfg, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "CppPluginsDir", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetBool(cpppluginpath, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "PythonPluginsDir", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetBool(pypluginpath, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "ExecInitScript", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetBool(execinitscr, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "LoadCppPlugins", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetBool(exectimerscr, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "ServerDir", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetString(serverdir, gt);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "ServerStartupCommand", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetString(servername, gt);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "JavaPath", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetString(javapath, gt);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "EnableMinecraftCommandQueue", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetBool(enablemccmdqueue, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "ServerParser", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetInt(parsertype, StringToParserCode(pElem->GetText()));
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "Instructionprefix", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetString(insprefix, gt);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "LogFilePath", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetString(logpath, gt);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "ScriptPath", pElem);
    if (pElem == NULL) return -1;
    GlobalSettings.SetString(scrpath, gt);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "Language", pElem);
    if (pElem == NULL) return -1;
    string str = gt;
    if (str == "en_US") {
        GlobalSettings.SetInt(lang, LANG_EN_US);
    }
    else if (str == "zh_CN") {
        GlobalSettings.SetInt(lang, LANG_ZH_CN);
    }
    dp("Read Config Successful.");

    dp("Exiting ReadCfgFile()");
    return 0;
}

bool LoadConfig::GetNodePointerByName(TiXmlElement* pRootEle, const char* strNodeName, TiXmlElement*& Node)    //此函数来自于CSDN 链接:https://blog.csdn.net/masikkk/article/details/14191933?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.add_param_isCf&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.add_param_isCf
{
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
    case lang:
        return iLangType;
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
    case servername:
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
    case lang:
        iLangType = value;
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
    case servername:
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