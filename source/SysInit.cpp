#include"SysInit.h"
#include"cfgfile.h"
#include"common.h"

int stdfuncallconv AnalyzeServerOutput(char* output);

int stdfuncallconv Initialize(){
    dp("Enter Initialize Function,start init now.");

    dp("Call LoadConfigFile Funtion");
    int loadcfgfileret = LoadConfig::LoadConfigFile();
    dp("LoadConfigFileReturns:" + loadcfgfileret);
    if (loadcfgfileret != 0)
        Cfg.SettingHelper();
    Out.Init(GlobalSettings.GetString(logpath));
#ifdef DEBUG_FUNC_ENABLE
    dp("Test OutputInterface.");
    Out.msg("Test");
    Out.warning("Test");
    Out.error("Test");
    Out.fatal("Test");
    Out.undef("Test");
#endif
    return 0;
}

int stdfuncallconv AnalyzeServerOutput(char* output) {
    return 0;
}

int stdfuncallconv Finalize() {
    return 0;
}

bool CheckFolderExist(const string& strPath)
{
    HANDLE hanTest;
    string folder;
    folder.append(".\\").append(strPath);
    return 0;
}

int stdfuncallconv DetectDir() {
    return 0;
}

int stdfuncallconv WelcomeMessage() {
    cout << "Welcome to MCDReforged By C++!Current Version : " << MCDRCPP_VER << '-' << MCDRCPP_DEV_STATUS << endl;
    cout << "You can check the new version at : " << MCDRCPP_RELEASES << endl;
    if (!MCDRCPP_ISSTABLE) cout << "This is not a stable version, If you find a bug, please send the program output, screenshot and the plugins you installed at the time of the error to the mailbox mcdrcpp_devteam@outlook.com" << endl;
    return 0;
}

int stdfuncallconv OpenServer()
{
    return 0;
}
