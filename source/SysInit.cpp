#include"SysInit.h"
#include"logsys.h"
#include"cfgfile.h"

int stdfuncallconv AnalyzeServerOutput(char* output);

int stdfuncallconv Initialize(){
    OutputInterface sysinitOut;
    LoadConfig Cfg;
    Settings GlobalSettings;
    dp("Enter Initialize Function,start init now.");

    dp("Call LoadConfigFile Funtion");
    int loadcfgfileret = LoadConfig::LoadConfigFile();
    dp("LoadConfigFileReturns:" + loadcfgfileret);
    if (loadcfgfileret != 0)
        Cfg.SettingHelper();
    sysinitOut.Init(GlobalSettings.GetString(logpath));
#ifdef DEBUG_FUNC_ENABLE
    dp("Test OutputInterface.");
    sysinitOut.msg("Test");
    sysinitOut.warning("Test");
    sysinitOut.error("Test");
    sysinitOut.fatal("Test");
    sysinitOut.undef("Test");
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
    Settings set;
    char javahome[512];
    strncpy(javahome, getenv("JAVA_HOME"), strlen(getenv("JAVA_HOME")));
    strcat(javahome, "\\bin\\java.exe");
    string startstr(javahome);
    startstr.append(set.GetString(serverdir)).append(set.GetString(servername));
    return 0;
}
