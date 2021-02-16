#include"systemfun.h"
#include"logsys.h"
#include"cfgfile.h"
#include"colorlog.h"
#include"pytools.h"
#include"redirectstdio.h"
#include"processinput.h"
#include"minecraftcmdqueue.h"

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

int stdfuncallconv Finalize(int exitcode) {
    CloseRedirect(&inf);
    cout << "Give me 3 second to prepare exiting...";
    cout << endl; 
    Sleep(3000);
    exit(exitcode);
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
