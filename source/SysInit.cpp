#include"SysInit.h"

#include"common.h"
#include"cfgfile.h"

#define IOBUFSIZE 4096

//������: ����stdin�ܵ������˾��
HANDLE hStdInRead, hStdInWrite;

//������: ����stdout�ܵ������˾��  
HANDLE hStdOutRead, hStdOutWrite;

//������:��ʹ��StdErr,��ʱʹ��StdOut
HANDLE hStdErrWrite;

STARTUPINFO si_startupinfo_struct;
PROCESS_INFORMATION pi_procinfo_struct;
SECURITY_ATTRIBUTES sa_attr_struct;

char* CmdLine;
char bufIn[IOBUFSIZE];
char bufOut[IOBUFSIZE];

DWORD Size1, Size2, process_exit_code;

int retvar;

BOOL stdfuncallconv ReadFromPipe(char* out_buffer, DWORD dwBufSize, DWORD& dwSize, int& iAnalyzeServerOutputReturn);
BOOL stdfuncallconv WriteToPipe(char* in_buffer, DWORD& dwSize);
int stdfuncallconv AnalyzeServerOutput(char* output);

int stdfuncallconv Initialize(){
    DebugPrint("Enter Initialize Function,start init now.");

    DebugPrint("Call LoadConfigFile Funtion");
    int loadcfgfileret = LoadConfig::LoadConfigFile();
    DebugPrint("LoadConfigFileReturns:" + loadcfgfileret);
    LoadConfig::Default();

	if (!CreatePipe(&hStdInRead, &hStdInWrite, &sa_attr_struct, 0))
		return -1;

    //����һ������stdout�Ĺܵ����õ�����HANDLE:  hStdInRead����������������ݣ�hStdInWrite�����ӳ���д������  
    if (!CreatePipe(&hStdOutRead, &hStdOutWrite, &sa_attr_struct, 0))
        return -1;
    //����stderrһ�����stdout, ֱ�Ӹ��ƾ��hStdOutWrite���õ� hStdErrWrite  
    if (!DuplicateHandle(GetCurrentProcess(), hStdOutWrite, GetCurrentProcess(), &hStdErrWrite, 0, TRUE, DUPLICATE_SAME_ACCESS))
        return -1;

    //��STARTUPINFO�ṹ�帳ֵ����stdin,stdout,stderr��Handle����Ϊ�ղŵõ��Ĺܵ�HANDLE  
    ZeroMemory(&si_startupinfo_struct, sizeof(STARTUPINFO));
    si_startupinfo_struct.cb = sizeof(STARTUPINFO);
    si_startupinfo_struct.dwFlags |= STARTF_USESHOWWINDOW;
    si_startupinfo_struct.dwFlags |= STARTF_USESTDHANDLES;
    si_startupinfo_struct.hStdOutput = hStdOutWrite;     //��˼�ǣ��ӽ��̵�stdout�����hStdOutWrite  
    si_startupinfo_struct.hStdError = hStdErrWrite;        //��˼�ǣ��ӽ��̵�stderr�����hStdErrWrite  
    si_startupinfo_struct.hStdInput = hStdInRead;

    // �����ӽ��̣��������˵����CreateProcess����  
    auto bSuccess = CreateProcess(NULL,
        CmdLine,    // �ӽ��̵�������  
        NULL,                   // process security attributes  
        NULL,                   // primary thread security attributes  
        TRUE,                   // handles are inherited  
        0,                          // creation flags  
        NULL,                  // use parent's environment  
        NULL,                  // use parent's current directory  
        &si_startupinfo_struct,      // STARTUPINFO pointer  
        &pi_procinfo_struct);     // receives PROCESS_INFORMATION  

     //���ʧ�ܣ��˳�  
    if (!bSuccess) return -1;

    //Ȼ�󣬾Ϳ��Զ�д�ܵ���  
    //д��stdin�����������һ��WriteToPipe������  
    WriteToPipe(bufIn, Size1);

    //�����Ӽ������з����  
    while (GetExitCodeProcess(pi_procinfo_struct.hProcess, &process_exit_code))
    {
        //��stdout,stderr  
        ReadFromPipe(bufOut, sizeof(bufOut), Size2, retvar);
        //����ӽ��̽������˳�ѭ��  
        if (process_exit_code != STILL_ACTIVE) break;
    }

    return 0;
}

BOOL stdfuncallconv WriteToPipe(char* in_buffer, DWORD& dwSize) {
    DWORD dwWritten;
    BOOL bSuccess = FALSE;

    //��WriteFile����hStdInWriteд�����ݣ�������in_buffer�У�����ΪdwSize  
    bSuccess = WriteFile(hStdInWrite, in_buffer, dwSize, &dwWritten, NULL);
    return bSuccess;
}

BOOL stdfuncallconv ReadFromPipe(char* out_buffer, DWORD dwBufSize, DWORD& dwSize, int& iAnalyzeServerOutputReturn) {
    BOOL bSuccess = FALSE;

    //��WriteFile����hStdOutRead�����ӽ���stdout��������ݣ����ݽ����out_buffer�У�����ΪdwRead  
    bSuccess = ReadFile(hStdOutRead, out_buffer, dwBufSize, &dwSize, NULL);
    if ((bSuccess) && (dwSize != 0))  //����ɹ��ˣ��ҳ���>0  
    {
        iAnalyzeServerOutputReturn = AnalyzeServerOutput(out_buffer);
    }
    return bSuccess;
}

int stdfuncallconv AnalyzeServerOutput(char* output) {
    return 0;
}

int stdfuncallconv Finalize() {
    return 0;
}

int stdfuncallconv GetJvmPath(string* strPath) {
    return 0;
}

bool CheckFolderExist(const string& strPath)
{
    WIN32_FIND_DATA  wfd;
    bool rValue = false;
    HANDLE hFind = FindFirstFile(strPath.c_str(), &wfd);
    if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
    {
        rValue = true;
    }
    FindClose(hFind);
    return rValue;
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