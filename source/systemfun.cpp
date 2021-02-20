#include"systemfun.h"

RedirectInformation riInf;
ServerInterface siInterface;
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
    
   
    return 0;
}

int stdfuncallconv DealWithUserInput() {
    string strUserInput;
    for (;;)
    {
        getline(cin, strUserInput);
        ProcessInput(strUserInput.c_str());
    }
    cout << endl;
}


int stdfuncallconv Finalize(int iexitcode) {
    CloseRedirect(&riInf);
    cout << "Give me 3 second to prepare exiting...";
    cout << endl; 
    Sleep(3000);
    exit(iexitcode);
}

int stdfuncallconv DetectDir() {
    return 0;                                                                           
}

int stdfuncallconv WelcomeMessage() {
    cout << "Welcome to MCDReforged By C++!Current Version : " << MCDRCPP_VER << '-' << MCDRCPP_DEV_STATUS << endl;
    cout << "You can check the new version at : " << MCDRCPP_RELEASES << endl;
    if (!MCDRCPP_ISSTABLE) cout << "This is not a stable version, If you find a bug, please send logs, screenshot and the plugins you installed at the time of the error to the mailbox mcdrcpp_devteam@outlook.com" << endl;
    cout << HINTMSG << endl;
    return 0;
}

int stdfuncallconv RunServer()
{
    siInterface.start(&riInf);
    return 0;
}
