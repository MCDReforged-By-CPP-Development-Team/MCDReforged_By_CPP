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
        char strCfgPath[MAX_PATH];
        GetModuleFileName(NULL, strCfgPath, MAX_PATH);
        (strrchr(strCfgPath, '\\'))[1] = 0;
        strcat_s(strCfgPath, "mcdrcppcfg.ini");

        string cfgPath = strCfgPath;

        return ReadCfgFile(cfgPath);
        return 0;
    }
    else {
        CreateCfgFile();
        return ReadCfgFile();
        return -1;
    }
}

int LoadConfig::CreateCfgFile() {

}

int LoadConfig::ReadCfgFile(string cfgFilePath) {

}