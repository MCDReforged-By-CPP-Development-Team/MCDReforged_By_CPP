#include"redirectstdio.h"
#include"utils.h"
RedirectInformation writeinf;

DWORD stdfuncallconv ServerSTDOUT(REDIRECT_INFORMATION priInfo, HANDLE hProc)
{
    dp("enter serverstdout");
    char out_buffer[BUFSIZE];
    DWORD dwRead;
    int iRet = FALSE;
    ProcessServerOutput output;
    DWORD process_exit_code;

    while (GetExitCodeProcess(hProc, &process_exit_code))
    {
        ZeroMemory(out_buffer, BUFSIZE);
        //用WriteFile，从hStdOutRead读出子进程stdout输出的数据，数据结果在out_buffer中，长度为dwRead  
        iRet = ReadFile(priInfo.hStdOutRead, out_buffer, BUFSIZE, &dwRead, NULL);
        if ((iRet) && (dwRead != 0))  //如果成功了，且长度>0  
        {
            output.ProcessOutput(out_buffer);
        }
        //如果子进程结束，退出循环  
        if (process_exit_code != STILL_ACTIVE) break;
    }
    return process_exit_code;
}

int stdfuncallconv CloseRedirect(PREDIRECT_INFORMATION priInformation)
{
    RedirectInformation inf = *priInformation;
    CloseHandle(inf.hStdErrWrite);
    CloseHandle(inf.hStdInRead);
    CloseHandle(inf.hStdInWrite);
    CloseHandle(inf.hStdOutRead);
    CloseHandle(inf.hStdOutWrite);
    return 1;
}

int stdfuncallconv OpenServerAndRedirectIO(PREDIRECT_INFORMATION priInformation)
{

    HANDLE hStdInRead = NULL;   //子进程用的stdin的读入端  
    HANDLE hStdInWrite = NULL;  //主程序用的stdin的读入端 
    HANDLE hStdOutRead = NULL;  //主程序用的stdout的读入端  
    HANDLE hStdOutWrite = NULL; //子进程用的stdout的写入端  
    HANDLE hStdErrWrite = NULL; //子进程用的stderr的写入端  

    Settings sets;
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    SECURITY_ATTRIBUTES sa;
    RedirectInformation inf;

    string servercmdline = sets.GetString(servername);
    string jvmpath = sets.GetString(javapath);
    string serverdir_ = sets.GetString(serverdir);
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    //产生一个用于stdin的管道，得到两个HANDLE:  hStdInRead用于子进程读出数据，hStdInWrite用于主程序写入数据  
    //其中saAttr是一个STARTUPINFO结构体，定义见CreatePipe函数说明  
    if (!CreatePipe(&hStdInRead, &hStdInWrite, &sa, 0))
        return -1;
    //产生一个用于stdout的管道，得到两个HANDLE:  hStdOutRead用于主程序读出数据，hStdOutWrite用于子程序写入数据  
    if (!CreatePipe(&hStdOutRead, &hStdOutWrite, &sa, 0))
        return -1;

    if (hStdInRead == NULL || hStdInWrite == NULL) return -1;
    if (hStdOutRead == NULL || hStdOutWrite == NULL) return -1;

    string startupcmd; 
    if (servercmdline.find(".bat") != string::npos || servercmdline.find(".cmd") != string::npos)//判断启动命令是否为bat或cmd文件
    {
        startupcmd = servercmdline;
        dp(startupcmd);
    }
    else//不是bat或cmd文件
    { 
      vector < string > vecstr = split(servercmdline, " ");//切丝
      startupcmd.append(jvmpath).append(" ");
      string servcmd;
      for (auto i : vecstr)//循环
      {
          if (i.find(".jar") != string::npos)
          {
               servcmd.append(serverdir_ + "\\" + i + " ");//加上服务器jar文件所在目录然后append
          }
          else
          {
               servcmd.append(i + " ");//不含有 .jar 的直接append
          }
      }
      startupcmd.append(servcmd);
      dp(startupcmd);
    }   

    LPSTR startcmd = new char[startupcmd.length() + 1];
    memset(startcmd, '\0', startupcmd.length() + 1);
    strcat_s(startcmd, startupcmd.length() + 1, startupcmd.c_str());
    dp("#");
    dp(startcmd);

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    si.hStdOutput = hStdOutWrite;   //意思是：子进程的stdout输出到hStdOutWrite  
    si.hStdError = hStdErrWrite;    //意思是：子进程的stderr输出到hStdErrWrite  
    si.hStdInput = hStdInRead;
#ifdef DEBUG_FUNC_ENABLE
    si.wShowWindow = SW_SHOW;
#else
    si.wShowWindow = SW_HIDE;
#endif

    // STARTF_USESHOWWINDOW:The wShowWindow member contains additional information.
    // STARTF_USESTDHANDLES:The hStdInput, hStdOutput, and hStdError members contain additional information.
    // from MSDN

    BOOL bSuc = CreateProcess(NULL
        , startcmd
        , NULL
        , NULL
        , TRUE
        , CREATE_SUSPENDED
        , NULL
        , NULL
        , &si
        , &pi);
    
    //CloseHandle(pi.hThread);

    if (bSuc == FALSE) { 
        dp("CreateProcess() Failed!");
        return -1;
    }

    inf = *priInformation;

    inf.hStdErrWrite = hStdErrWrite;
    inf.hStdInRead = hStdInRead;
    inf.hStdInWrite = hStdInWrite;
    inf.hStdOutRead = hStdOutRead;
    inf.hStdOutWrite = hStdOutWrite;

    dp("pid:" + pi.dwProcessId);
    dp("tid:" + pi.dwThreadId);
    thread ServerOut(ServerSTDOUT, inf, pi.hProcess);
    ServerOut.detach();
    Sleep(1);
    ResumeThread(pi.hThread);
    
    dp("##############################################");
    delete[] startcmd;
    startcmd = NULL;
    dp("###############################################");

    writeinf = inf;

    return 0;
}   //此函数部分代码来自 https://blog.csdn.net/breaksoftware/article/details/8595734 , https://blog.csdn.net/dicuzhaoqin8950/article/details/102229723 同时感谢作者

int stdfuncallconv WriteToPipe(const char *in_buffer, DWORD dwSize) {
    DWORD dwWritten;
    int iRet = FALSE;

    //用WriteFile，从hStdInWrite写入数据，数据在in_buffer中，长度为dwSize  
    iRet = WriteFile(writeinf.hStdInWrite, in_buffer, dwSize, &dwWritten, NULL);
    iRet = WriteFile(writeinf.hStdInWrite, "\r\n", 2, &dwWritten, NULL);
    return iRet;
}

