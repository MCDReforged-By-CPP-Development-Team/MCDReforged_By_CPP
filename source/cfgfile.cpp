#include"cfgfile.h"

LoadConfig Cfg;
Settings GlobalSettings;
OutputInterface Out;

using namespace std;

#pragma region Definitions
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
#pragma endregion

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
    if (Cfg.ConfigFileExisting()) {
        return Cfg.ReadCfgFile();
    }
    else {
        Cfg.CreateCfgFile();
        Cfg.SettingHelper();
        return Cfg.ReadCfgFile();
    }
    return -1;
}

int gsti() {
    strstream str;
    string str_pre;
    cin >> str_pre;
    str << str_pre;
    int ret;
    str >> ret;
    return ret;
}
bool gstb() {
    string str;
    cin >> str;
    if (str == "Y" || str == "y") {
        return true;
    }
    else if (str == "N" || str == "n") {
        return false;
    }
    return true;
}
#define iner Out.mlout("Please input a vaild value", "请输入一个有效值")
int stdfuncallconv LoadConfig::SettingHelper()
{
    int ivar;
    bool bvar;
    string svar;

    Out.mlout("Welcome to SettingHelper.", "欢迎来到配置文件设置助手");
    Out.mlout("Choose Your Language[English(US)-0][简体中文-1]",
        "选择您的语言[English(US)-0][简体中文-1]");  //iLangType
language:
    ivar = gsti();
    if (ivar != LANG_ZH_CN && ivar != LANG_EN_US) {
        iner;
        goto language;
    }
    GlobalSettings.SetInt(lang, ivar);

    Out.mlout("Select Your Server Type[Vanilla-0][Bukkit(Version<1.14)-1][Bukkit(Version>=1.14)][BungeeCord-3][Cat-4][Waterfall-5][Beta1.8-6][Forge-7]",
              "请选择您的服务器端类型[Vanilla-0][Bukkit(Version<1.14)-1][Bukkit(Version>=1.14)][BungeeCord-3][Cat-4][Waterfall-5][Beta1.8-6][Forge-7]");   //iParserType
    parser:
    ivar = gsti();
    if (ivar > FORGE_PARSER_CODE || ivar < VANILLA_PARSER_CODE) { 
        iner;
        goto parser;
    }
    GlobalSettings.SetInt(parsertype, ivar);

    Out.mlout("Load C++ Plugins?[Y/N]",
        "装载C++插件?[Y/N]");   //bLoadCppPlugins
    bvar = gstb();
    GlobalSettings.SetBool(loadcppplugins, bvar);

    Out.mlout("Load Python Plugins?[Y/N]",
        "装载Python插件?[Y/N]");   //bLoadPyPlugins
    bvar = gstb();
    GlobalSettings.SetBool(loadpyplugins, bvar);

    Out.mlout("Execute initialization script when the application start?[Y/N]",
        "在启动时运行初始化脚本?[Y/N]");   //bExecInitScript
    bvar = gstb();
    GlobalSettings.SetBool(execinitscr, bvar);

    Out.mlout("Execute timer script?[Y/N]",
        "运行定时脚本?[Y/N]");   //bExecTimerScript
    bvar = gstb();
    GlobalSettings.SetBool(exectimerscr, bvar);

    Out.mlout("Read C++ plugin configs?[Y/N]",
        "读取C++插件配置文件?[Y/N]");   //bReadCppPluginsCfg
    bvar = gstb();
    GlobalSettings.SetBool(readcpppluginscfg, bvar);

    Out.mlout("Read Python plugin configs?[Y/N]",
        "读取Python插件配置文件?[Y/N]");   //bReadPyPluginsCfg
    bvar = gstb();
    GlobalSettings.SetBool(readpypluginscfg, bvar);

    Out.mlout("Enable Minecraft command queue(Enable is recommended)?[Y/N]",
        "开启Minecraft指令队列功能(建议开启)?[Y/N]");   //bEnableMinecraftCommandQueue
    bvar = gstb();
    GlobalSettings.SetBool(enablemccmdqueue, bvar);

readjavapath:
    Out.mlout("We need your Java path(Type \"autofind\" to find the Java automatically.When you type it, all lowercase characters are required)",
        "我们需要您的Java路径(输入\"autofind\"以自动寻找Java,如输入则要求全小写)");   //strJavaPath
    getline(cin, svar);
    if (svar == "autofind") {
        svar = getenv("JAVA_HOME");
        svar.append("bin\\javaw.exe");
        Out.msg("Java path : " + svar);
        Out.mlout("If the Java path is right,type \"Y\" or \"y\" to confirm. If the Java path is wrong,type \"N\" or \"n\" to type the path manually."
            , "如果Java路径正确,请键入\"Y\"或\"y\"进行确认.如果Java路径错误,请键入\"N\"或\"n\"手动键入路径.");
        bvar = gstb();
        if (!bvar)goto readjavapath;
    }
    GlobalSettings.SetString(javapath, svar);

    Out.mlout("Your Minecraft server's folder name?",
        "您Minecraft服务器的文件夹名?");   //strServerWorkingDir
    getline(cin, svar);
    GlobalSettings.SetString(serverdir, svar);

    Out.mlout("Minecraft server startup parameters?(Enter parameters only, excluding java's name.For example:-Xms1G -Xmx2G -jar minecraft_server.jar nogui)",
        "Minecraft服务器启动参数?(仅输入参数,不包括Java程序名.示例:-Xms1G -Xmx2G -jar minecraft_server.jar nogui)");   //strMinecraftServerStartupCommandLine
    getline(cin, svar);
    GlobalSettings.SetString(servername, svar);

    Out.mlout("C++ plugins' folder name?(\"plugins\" is recommended)",
        "C++插件文件夹名(推荐使用\"plugins\")");   //strCppPluginPath
    getline(cin, svar);
    GlobalSettings.SetString(cpppluginpath, svar);

    Out.mlout("Python plugins' folder name?(\"plugins\" is recommended)",
        "Python插件文件夹名(推荐使用\"plugins\")");   //strPyPluginPath
    getline(cin, svar);
    GlobalSettings.SetString(pypluginpath, svar);

    Out.mlout("Scripts' Path?(\"scripts\" is recommended)",
        "脚本文件夹名?(推荐使用\"scripts\")");   //strScriptPath
    getline(cin, svar);
    GlobalSettings.SetString(scrpath, svar);

    Out.mlout("MCDReforged by C++ command prefix?(In order to keep compatible with MCDReforged,\"!!MCDR\" is strongly recommended)",
        "MCDReforged by C++指令前缀(为了与MCDReforged保持高度兼容,强烈推荐使用\"!!MCDR\")");   //strInstructionPrefix
    getline(cin, svar);
    GlobalSettings.SetString(insprefix, svar);

    Out.mlout("Select a folder that the log files will be stored in,the folder will be created automatically.",
        "选择要存储日志文件的文件夹,该文件夹将自动创建.");   //strLogFilePath
    getline(cin, svar);
    GlobalSettings.SetString(logpath, svar);
settocfg_:
    return Cfg.SetToCfg();
}
/*
iParserType[ok];iLangType[ok];bLoadCppPlugins[ok];bLoadPyPlugins[ok];bExecInitScript[ok];bExecTimerScript[ok];bReadCppPluginsCfg[ok];bReadPyPluginsCfg[ok];
bEnableMinecraftCommandQueue[ok];
strJavaPath[ok];strServerWorkingDir[ok];strMinecraftServerStartupCommandLine[ok];strCppPluginPath[ok];strPyPluginPath[ok];strScriptPath[ok];
strInstructionPrefix[ok];
strLogFilePath[ok];
*/

int stdfuncallconv LoadConfig::SetToCfg()   //有bug 会死循环
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
    dp("create doc and decl successfully.");
    pDoc->LinkEndChild(pDeclaration);
    TiXmlElement* pRootEle = new TiXmlElement("MCDReforgedByCppConfig");
    if (NULL == pRootEle)
    {
        return false;
    }
    pDoc->LinkEndChild(pRootEle);
    string strValue;
    
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
    SETTOCFG_S("ScriptPath", ScriptPath, scrpath);
    pDoc->SaveFile(CFGFILENAME);
    return true;
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
    int iret = 0;
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

    GetNodePointerByName(pRootEle, "LoadCppPlugins", pElem);
    rettest
    GlobalSettings.SetBool(loadcppplugins, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "LoadPythonPlugins", pElem);
    rettest
    GlobalSettings.SetBool(loadpyplugins, stb);
    dp("Read Config Successful.");  

    GetNodePointerByName(pRootEle, "LoadCppPluginsConfig", pElem);
    rettest
    GlobalSettings.SetBool(readcpppluginscfg, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "LoadPythonPluginsConfig", pElem);
    rettest
    GlobalSettings.SetBool(readpypluginscfg, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "CppPluginsDir", pElem);
    rettest
    GlobalSettings.SetBool(cpppluginpath, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "PythonPluginsDir", pElem);
    rettest
    GlobalSettings.SetBool(pypluginpath, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "ExecInitScript", pElem);
    rettest
    GlobalSettings.SetBool(execinitscr, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "LoadCppPlugins", pElem);
    rettest
    GlobalSettings.SetBool(exectimerscr, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "ServerDir", pElem);
    rettest
    GlobalSettings.SetString(serverdir, gt);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "ServerStartupCommand", pElem);
    rettest
    GlobalSettings.SetString(servername, gt);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "JavaPath", pElem);
    rettest
    GlobalSettings.SetString(javapath, gt);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "EnableMinecraftCommandQueue", pElem);
    rettest
    GlobalSettings.SetBool(enablemccmdqueue, stb);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "ServerParser", pElem);
    rettest
    GlobalSettings.SetInt(parsertype, StringToParserCode(pElem->GetText()));
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "Instructionprefix", pElem);
    rettest
    GlobalSettings.SetString(insprefix, gt);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "LogFilePath", pElem);
    rettest
    GlobalSettings.SetString(logpath, gt);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "ScriptPath", pElem);
    rettest
    GlobalSettings.SetString(scrpath, gt);
    dp("Read Config Successful.");

    GetNodePointerByName(pRootEle, "Language", pElem);
    rettest
    string str = gt;
    if (str == "en_US") {
        GlobalSettings.SetInt(lang, LANG_EN_US);
    }
    else if (str == "zh_CN") {
        GlobalSettings.SetInt(lang, LANG_ZH_CN);
    }
    dp("Read Config Successful.");

    dp("exiting readcfg");
    return iret;
}

bool LoadConfig::GetNodePointerByName(TiXmlElement* pRootEle, const char* strNodeName, TiXmlElement*& Node)    //此函数来自于CSDN 略有改动 链接:https://blog.csdn.net/masikkk/article/details/14191933?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.add_param_isCf&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.add_param_isCf
{
    if (0 == strcmp(strNodeName, pRootEle->Value()))
    {
        Node = pRootEle;
        return true;
    }

    TiXmlElement* pEle = pRootEle;
    for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement())
    {
        if (0 != strcmp(pEle->Value(), strNodeName))
        {
            GetNodePointerByName(pEle, strNodeName, Node);
        }
        else
        {
            Node = pEle;
            return true;
        }
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

void stdfuncallconv Settings::SetInt(int set, int value)
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
        return ;
        break;
    }
    return ;
}

void stdfuncallconv Settings::SetBool(int set, bool value)
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
    return ;
}

void stdfuncallconv Settings::SetString(int set, string value)
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
    return ;
}

void stdfuncallconv Settings::SetString(int set, LPSTR value)
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
    return ;
}

void stdfuncallconv Settings::SetString(int set, LPCSTR value)
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
    return ;
}
