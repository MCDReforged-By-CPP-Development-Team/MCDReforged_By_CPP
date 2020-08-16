#include"cfgfile.h"
#include<Windows.h>
#include<string>

bool LoadConfig::ConfigFileExisting() {
    char strCfgPath[MAX_PATH];
    GetModuleFileName(NULL, strCfgPath, MAX_PATH);
    (strrchr(strCfgPath, '\\'))[1] = 0;
    strcat_s(strCfgPath, "mcdrcppcfg.ini"); //��ȡmcdrcpp�����ļ�·��

    HANDLE hFile = ::CreateFile(
        strCfgPath,
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        0);
    if (hFile == INVALID_HANDLE_VALUE) return false;    //�ж�mcdrcpp�����ļ��Ƿ����
    CloseHandle(hFile);
    return true;
}

int LoadConfig::LoadConfigFile() {
    if (ConfigFileExisting()) {
        return 0;
    }
    else {
        CreateCfgFile();
        return -1;
    }
}

int LoadConfig::CreateCfgFile() {

}