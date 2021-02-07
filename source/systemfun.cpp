#include"systemfun.h"
#include"logsys.h"
#include"cfgfile.h"
#include"colorlog.h"
#include"pytools.h"
#include"redirectstdio.h"
#include"processinput.h"

int stdfuncallconv AnalyzeServerOutput(char* output);
RedirectInformation inf;
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
    dp("CreatingDirs");
    
    dp(CreateDirectory(GlobalSettings.GetString(logpath).c_str(),NULL));
    //CreateDirectory(GlobalSettings.GetString(serverd).c_str(), NULL);
    dp(CreateDirectory(GlobalSettings.GetString(scrpath).c_str(), NULL));
    dp(CreateDirectory(GlobalSettings.GetString(cpppluginpath).c_str(), NULL));
    dp(CreateDirectory(GlobalSettings.GetString(pypluginpath).c_str(), NULL));

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
    pytTools.InstallPyLibAsync("colorama");
    Sleep(1000);
    dp(GlobalSettings.GetString(servername));
    dp(GlobalSettings.GetString(javapath));
#endif
    system("pause");
    auto openserverret = OpenServerAndRedirectIO(&inf);

    string strUserInput;
    for (;;)
    {
        getline(cin, strUserInput);
        ProcessInput(strUserInput.c_str());
    }
    cout << endl;

    return 0;
}

int stdfuncallconv AnalyzeServerOutput(char* output) {

    return 0;
}

int stdfuncallconv Finalize() {
    CloseRedirect(&inf);
    cout << "Give me 3 second to prepare exiting...";
    cout << endl; 
    Sleep(3000);
    return 0;
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
