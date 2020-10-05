#include"SysInit.h"

#define IOBUFSIZE 4096

//定义句柄: 构成stdin管道的两端句柄
HANDLE hStdInRead, hStdInWrite;

//定义句柄: 构成stdout管道的两端句柄  
HANDLE hStdOutRead, hStdOutWrite;

//定义句柄:不使用StdErr,暂时使用StdOut
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
    InitDebugPrint("Enter Initialize Function,start init now.");

    InitDebugPrint("Call LoadConfigFile Funtion");
    auto loadcfgfileret = LoadConfig::LoadConfigFile();
    InitDebugPrint("LoadConfigFileReturns:" + loadcfgfileret);

	if (!CreatePipe(&hStdInRead, &hStdInWrite, &sa_attr_struct, 0))
		return -1;

    //产生一个用于stdout的管道，得到两个HANDLE:  hStdInRead用于主程序读出数据，hStdInWrite用于子程序写入数据  
    if (!CreatePipe(&hStdOutRead, &hStdOutWrite, &sa_attr_struct, 0))
        return -1;
    //由于stderr一般就是stdout, 直接复制句柄hStdOutWrite，得到 hStdErrWrite  
    if (!DuplicateHandle(GetCurrentProcess(), hStdOutWrite, GetCurrentProcess(), &hStdErrWrite, 0, TRUE, DUPLICATE_SAME_ACCESS))
        return -1;

    //对STARTUPINFO结构体赋值，对stdin,stdout,stderr的Handle设置为刚才得到的管道HANDLE  
    ZeroMemory(&si_startupinfo_struct, sizeof(STARTUPINFO));
    si_startupinfo_struct.cb = sizeof(STARTUPINFO);
    si_startupinfo_struct.dwFlags |= STARTF_USESHOWWINDOW;
    si_startupinfo_struct.dwFlags |= STARTF_USESTDHANDLES;
    si_startupinfo_struct.hStdOutput = hStdOutWrite;     //意思是：子进程的stdout输出到hStdOutWrite  
    si_startupinfo_struct.hStdError = hStdErrWrite;        //意思是：子进程的stderr输出到hStdErrWrite  
    si_startupinfo_struct.hStdInput = hStdInRead;

    // 产生子进程，具体参数说明见CreateProcess函数  
    auto bSuccess = CreateProcess(NULL,
        CmdLine,    // 子进程的命令行  
        NULL,                   // process security attributes  
        NULL,                   // primary thread security attributes  
        TRUE,                   // handles are inherited  
        0,                          // creation flags  
        NULL,                  // use parent's environment  
        NULL,                  // use parent's current directory  
        &si_startupinfo_struct,      // STARTUPINFO pointer  
        &pi_procinfo_struct);     // receives PROCESS_INFORMATION  

     //如果失败，退出  
    if (!bSuccess) return -1;

    //然后，就可以读写管道了  
    //写入stdin，具体代码在一个WriteToPipe函数中  
    WriteToPipe(bufIn, Size1);

    //不断子检测进程有否结束  
    while (GetExitCodeProcess(pi_procinfo_struct.hProcess, &process_exit_code))
    {
        //读stdout,stderr  
        ReadFromPipe(bufOut, sizeof(bufOut), Size2, retvar);
        //如果子进程结束，退出循环  
        if (process_exit_code != STILL_ACTIVE) break;
    }

    return 0;
}

BOOL stdfuncallconv WriteToPipe(char* in_buffer, DWORD& dwSize) {
    DWORD dwWritten;
    BOOL bSuccess = FALSE;

    //用WriteFile，从hStdInWrite写入数据，数据在in_buffer中，长度为dwSize  
    bSuccess = WriteFile(hStdInWrite, in_buffer, dwSize, &dwWritten, NULL);
    return bSuccess;
}

BOOL stdfuncallconv ReadFromPipe(char* out_buffer, DWORD dwBufSize, DWORD& dwSize, int& iAnalyzeServerOutputReturn) {
    BOOL bSuccess = FALSE;

    //用WriteFile，从hStdOutRead读出子进程stdout输出的数据，数据结果在out_buffer中，长度为dwRead  
    bSuccess = ReadFile(hStdOutRead, out_buffer, dwBufSize, &dwSize, NULL);
    if ((bSuccess) && (dwSize != 0))  //如果成功了，且长度>0  
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

int stdfuncallconv InitDebugPrint(string str) {
	cout << "[InitDebugPrint] : " << str << endl;
	return 0;
}
