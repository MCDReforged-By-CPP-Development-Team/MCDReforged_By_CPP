#include"SysInit.h"
#include"logsys.h"
#include"cfgfile.h"
#include"colorlog.h"
#include"pytools.h"
#include"redirectstdio.h"

int stdfuncallconv AnalyzeServerOutput(char* output);

int stdfuncallconv Initialize(){
    Sleep(1000);
    OutputInterface sysinitOut;
    LoadConfig Cfg;
    Settings GlobalSettings;
    ColorLog log;
    dp("Enter Initialize Function,start init now.");

    SetConsoleTitle("MCDReforged by C++");

    dp("Call LoadConfigFile Funtion");
    int loadcfgfileret = LoadConfig::LoadConfigFile();
    dp("LoadConfigFileReturns:" + loadcfgfileret);
    sysinitOut.Init(GlobalSettings.GetString(logpath));

#ifdef DEBUG_FUNC_ENABLE
    dp("Test OutputInterface.");
    sysinitOut.msg("Test");
    sysinitOut.warning("Test");
    sysinitOut.error("Test");
    sysinitOut.fatal("Test");
    sysinitOut.undef("Test");
    dp("Test Colorlog");
    log.out("C", RED_FOREGROUND);
    log.out("o", GREEN_FOREGROUND);
    log.out("l", BLUE_FOREGROUND);
    log.out("o", LIME_FOREGROUND);
    log.out("r", PURPLE_FOREGROUND);
    log.out("L", YELLOW_FOREGEOUND);
    log.out("o", RED_FOREGROUND);
    log.out("g", GREEN_FOREGROUND);
    cout << endl;
    dp("Test Pytools & MultiThread");
    Pytools pytTools(sysinitOut);
    pytTools.InstallPyLibAsync("cyka_blyat");

    dp("pip0");
    Sleep(1000);
    dp("pip0");
    Sleep(1000);
    dp("pip0");
    Sleep(1000);
    dp("pip0");
    Sleep(1000);
    dp("pip0");
    dp(GlobalSettings.GetString(servername));
    dp(GlobalSettings.GetString(javapath));
#endif
    RedirectInformation inf;

    auto openserverret = OpenServerAndRedirectIO(&inf);
    CloseRedirect(&inf);
    return 0;
}

int stdfuncallconv AnalyzeServerOutput(char* output) {
    return 0;
}

int stdfuncallconv Finalize() {
    cout << "Give me 3 second to prepare exiting...";
    cout << endl; 
    Sleep(3000);
    return 0;
}
//寻找文件夹是否存在 strpath:目录
//返回true即为文件夹存在 返回false为文件夹不存在或者为文件
bool CheckFolderExist(const string& strPath){
    HANDLE hTest;
    string folder;
    folder.append(".\\").append(strPath);
    WIN32_FIND_DATA wfdFind;
    hTest = FindFirstFile(folder.c_str(), &wfdFind);
    if ((hTest == INVALID_HANDLE_VALUE ) && wfdFind.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
    {
        FindClose(hTest);
        return true;
    }
    return false;
}

int stdfuncallconv DetectDir() {
    return 0;                                                                           
}

int stdfuncallconv WelcomeMessage() {
    cout << "Welcome to MCDReforged By C++!Current Version : " << MCDRCPP_VER << '-' << MCDRCPP_DEV_STATUS << endl;
    cout << "You can check the new version at : " << MCDRCPP_RELEASES << endl;
    if (!MCDRCPP_ISSTABLE) cout << "This is not a stable version, If you find a bug, please send the program output, screenshot and the plugins you installed at the time of the error to the mailbox mcdrcpp_devteam@outlook.com" << endl;
    cout << HINTMSG << endl;
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
