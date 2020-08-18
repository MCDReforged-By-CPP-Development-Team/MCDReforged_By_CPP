#include"cfgfile.h"

using namespace std;

bool LoadConfig::ConfigFileExisting() {
    char strCfgPath[MAX_PATH];
    GetModuleFileName(NULL, strCfgPath, MAX_PATH);
    (strrchr(strCfgPath, '\\'))[1] = 0;
    strcat_s(strCfgPath, "mcdrcppcfg.ini"); //获取mcdrcpp配置文件路径

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
    if (ConfigFileExisting()) {
        char pathBuf[MAX_PATH];
        GetCurrentDirectoryA(sizeof(pathBuf), pathBuf);
        strcat_s(pathBuf, "mcdrcppconfig.xml");

        string cfgPath = pathBuf;

        return ReadCfgFile(cfgPath);
        return 0;
    }
    else {
        CreateCfgFile();
        char pathBuf[MAX_PATH];
        GetCurrentDirectoryA(sizeof(pathBuf), pathBuf);
        strcat_s(pathBuf, "mcdrcppconfig.xml");

        string cfgPath = pathBuf;

        return ReadCfgFile(pathBuf);
        return -1;
    }
}

int LoadConfig::CreateCfgFile() {
    return 0;
}

int LoadConfig::ReadCfgFile(string cfgFilePath) {
    TiXmlDocument *pDoc = new TiXmlDocument;
    if (pDoc == NULL) return -1;

    pDoc->LoadFile(cfgFilePath.c_str());
    TiXmlElement* pRootEle = pDoc->RootElement();
    if (pRootEle == NULL) return -1;

    TiXmlElement* pElem = NULL;

    GetNodePointerByName(pRootEle, (string)"LoadCppPlugins", pElem);
    if (pElem == NULL) return -1;
    Globalsettings::bLoadCppPlugins = StringToBool(pElem->GetText());

    GetNodePointerByName(pRootEle, (string)"LoadPythonPlugins", pElem);
    if (pElem == NULL) return -1;
    Globalsettings::bLoadPyPlugins = StringToBool(pElem->GetText());

    GetNodePointerByName(pRootEle, (string)"LoadCppPluginsConfig", pElem);
    if (pElem == NULL) return -1;
    Globalsettings::bReadCppPluginsCfg = StringToBool(pElem->GetText());

    GetNodePointerByName(pRootEle, (string)"LoadPythonPluginsConfig", pElem);
    if (pElem == NULL) return -1;
    Globalsettings::bReagPyPluginCfg = StringToBool(pElem->GetText());

    GetNodePointerByName(pRootEle, (string)"CppPuginsDir", pElem);
    if (pElem == NULL) return -1;
    Globalsettings::strCppPluginPath = pElem->GetText();

    GetNodePointerByName(pRootEle, (string)"PythonPluginsDir", pElem);
    if (pElem == NULL) return -1;
    Globalsettings::strPyPluginPath = pElem->GetText();

    GetNodePointerByName(pRootEle, (string)"ExecInitScript", pElem);
    if (pElem == NULL) return -1;
    Globalsettings::bExecInitScript = StringToBool(pElem->GetText());

    GetNodePointerByName(pRootEle, (string)"LoadCppPlugins", pElem);
    if (pElem == NULL) return -1;
    Globalsettings::bExecTimerScript = StringToBool(pElem->GetText());

    GetNodePointerByName(pRootEle, (string)"ServerDir", pElem);
    if (pElem == NULL) return -1;
    Globalsettings::strServerWorkingDir = pElem->GetText();

    GetNodePointerByName(pRootEle, (string)"PythonPluginsDir", pElem);
    if (pElem == NULL) return -1;
    Globalsettings::strMinecraftServerFileName = pElem->GetText();

    GetNodePointerByName(pRootEle, (string)"JavaPath", pElem);
    if (pElem == NULL) return -1;
    Globalsettings::strJavaPath = pElem->GetText();

    GetNodePointerByName(pRootEle, (string)"EnableMinecraftCommandQueue", pElem);
    if (pElem == NULL) return -1;
    Globalsettings::bEnableMinecraftCommandQueue = StringToBool(pElem->GetText());

    return 0;
}

bool LoadConfig::GetNodePointerByName(TiXmlElement* pRootEle, std::string& strNodeName, TiXmlElement*& Node)    //此函数来自于CSDN 链接:https://blog.csdn.net/masikkk/article/details/14191933?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.add_param_isCf&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.add_param_isCf
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