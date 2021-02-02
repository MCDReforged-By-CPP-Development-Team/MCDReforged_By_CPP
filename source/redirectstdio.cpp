﻿#include"redirectstdio.h"

int stdfuncallconv OpenServerAndRedirectIO(PREDIRECT_INFORMATION priInformation)
{

    HANDLE hStdInRead = NULL;   //子进程用的stdin的读入端  
    HANDLE hStdInWrite = NULL;  //主程序用的stdin的读入端 
    HANDLE hStdOutRead = NULL;  //主程序用的stdout的读入端  
    HANDLE hStdOutWrite = NULL; //子进程用的stdout的写入端  
    HANDLE hStdErrWrite = NULL; //子进程用的stderr的写入端  

    ProcessServerOutput output;
    DWORD process_exit_code;
	Settings sets;
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    SECURITY_ATTRIBUTES sa;

	string servercmdline = sets.GetString(servername);
	string jvmpath = sets.GetString(javapath);

    char out_buffer[4096];
    DWORD dwRead;
    int iRet = FALSE;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;

    //产生一个用于stdin的管道，得到两个HANDLE:  hStdInRead用于子进程读出数据，hStdInWrite用于主程序写入数据  
    //其中saAttr是一个STARTUPINFO结构体，定义见CreatePipe函数说明  
    if (!CreatePipe(&hStdInRead, &hStdInWrite, &sa, 0))
        return -1;
    //产生一个用于stdout的管道，得到两个HANDLE:  hStdInRead用于主程序读出数据，hStdInWrite用于子程序写入数据  
    if (!CreatePipe(&hStdOutRead, &hStdOutWrite, &sa, 0))
        return -1;

    if (hStdInRead == NULL || hStdInWrite == NULL) return -1;
    if (hStdOutRead == NULL || hStdOutWrite == NULL) return -1;

    string startupcmd;
    startupcmd.append(jvmpath).append(" ").append(servercmdline);

    LPSTR startcmd = new char[startupcmd.length() + 1];
    memset(startcmd, '\0', startupcmd.length() + 1);
    strcat_s(startcmd, startupcmd.length() + 1, startupcmd.c_str());
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
        , NULL
        , NULL
        , NULL
        , &si
        , &pi);
    
    if (bSuc == FALSE) { 
        dp("CreateProcess() Failed!");
        return -1;
    }

    // 先分配读取的数据空间
    DWORD dwTotalSize = NEWBUFFERSIZE;                     // 总空间
    char* pchReadBuffer = new char[dwTotalSize];
    memset(pchReadBuffer, 0, NEWBUFFERSIZE);

    DWORD dwFreeSize = dwTotalSize;                 // 闲置空间
    /*
    dp("entering dowhile");
    do {
        if (FALSE == bSuc) {
            break;
        }

        // 重置成功标志，之后要视读取是否成功来决定
        bSuc = FALSE;

        char chTmpReadBuffer[NEWBUFFERSIZE] = { 0 };
        DWORD dwbytesRead = 0;

        // 用于控制读取偏移
        OVERLAPPED Overlapped;
        memset(&Overlapped, 0, sizeof(OVERLAPPED));

        while (GetExitCodeProcess(pi.hProcess, &process_exit_code)) {
            
            // 清空缓存
            memset(chTmpReadBuffer, 0, NEWBUFFERSIZE);

            // 读取管道
            BOOL bRead = ReadFile(hStdInRead, chTmpReadBuffer, NEWBUFFERSIZE, &dwbytesRead, &Overlapped);
            DWORD dwLastError = GetLastError();
            dp("dwLastError : " + dwLastError);

            if (bRead) {
                if (dwFreeSize >= dwbytesRead) {
                    // 空闲空间足够的情况下，将读取的信息拷贝到剩下的空间中
                    memcpy_s(pchReadBuffer + Overlapped.Offset, dwFreeSize, chTmpReadBuffer, dwbytesRead);
                    // 重新计算新空间的空闲空间
                    dwFreeSize -= dwbytesRead;
                }
                else {
                    // 计算要申请的空间大小
                    DWORD dwAddSize = (1 + dwbytesRead / NEWBUFFERSIZE) * NEWBUFFERSIZE;
                    // 计算新空间大小
                    DWORD dwNewTotalSize = dwTotalSize + dwAddSize;
                    // 计算新空间的空闲大小
                    dwFreeSize += dwAddSize;
                    // 新分配合适大小的空间
                    char* pTempBuffer = new char[dwNewTotalSize];
                    // 清空新分配的空间
                    memset(pTempBuffer, 0, dwNewTotalSize);
                    // 将原空间数据拷贝过来
                    memcpy_s(pTempBuffer, dwNewTotalSize, pchReadBuffer, dwTotalSize);
                    // 保存新的空间大小
                    dwTotalSize = dwNewTotalSize;
                    // 将读取的信息保存到新的空间中
                    memcpy_s(pTempBuffer + Overlapped.Offset, dwFreeSize, chTmpReadBuffer, dwbytesRead);
                    // 重新计算新空间的空闲空间
                    dwFreeSize -= dwbytesRead;
                    // 将原空间释放掉
                    delete[] pchReadBuffer;
                    // 将原空间指针指向新空间地址
                    pchReadBuffer = pTempBuffer;
                }

                // 读取成功，则继续读取，设置偏移
                Overlapped.Offset += dwbytesRead;
            }
            else {
                if (ERROR_BROKEN_PIPE == dwLastError) {
                    bSuc = TRUE;
                }
                break;
            }

            if (output.ProcessOutput(pchReadBuffer,0) == -1) { 
                dp("Cannot Process Server's Output.");
                output.CannotProcessOutput(); 
            }

            if (process_exit_code != STILL_ACTIVE) { 
                dp("Server exited with exit code : " + process_exit_code);
                break; 
            }
        }
    } while (0);
    */
    GetExitCodeProcess(pi.hProcess, &process_exit_code);
    dp((int)process_exit_code);
    while (GetExitCodeProcess(pi.hProcess, &process_exit_code))
    {
        //用WriteFile，从hStdOutRead读出子进程stdout输出的数据，数据结果在out_buffer中，长度为dwRead  
        iRet = ReadFile(hStdOutRead, out_buffer, BUFSIZE, &dwRead, NULL);
        dp((int)dwRead);
        if ((iRet) && (dwRead != 0))  //如果成功了，且长度>0  
        {
            dp("process output");
            output.ProcessOutput(out_buffer);
        }
        //如果子进程结束，退出循环  
        if (process_exit_code != STILL_ACTIVE) break;
    }

    delete[] pchReadBuffer;
    delete[] startcmd;
    startcmd = NULL;
    pchReadBuffer = NULL;
    RedirectInformation inf;
    inf = *priInformation;

    inf.hStdErrWrite = hStdErrWrite;
    inf.hStdInRead = hStdInRead;
    inf.hStdInWrite = hStdInWrite;
    inf.hStdOutRead = hStdOutRead;
    inf.hStdOutWrite = hStdOutWrite;

    return bSuc;
}   //此函数部分代码来自 https://blog.csdn.net/breaksoftware/article/details/8595734 , https://blog.csdn.net/dicuzhaoqin8950/article/details/102229723 同时感谢作者

int WriteToPipe(HANDLE hWrite, char *in_buffer, DWORD dwSize) {
    DWORD dwWritten;
    int iRet = FALSE;

    //用WriteFile，从hStdInWrite写入数据，数据在in_buffer中，长度为dwSize  
    iRet = WriteFile(hWrite, in_buffer, dwSize, &dwWritten, NULL);
    return iRet;
}

int stdfuncallconv CloseRedirect(PREDIRECT_INFORMATION priInformation, PINT TerminateProcessReturn)
{
    int iRet = TRUE;
    UINT exitcode;

    RedirectInformation inf = *priInformation;
    CloseHandle(inf.hStdErrWrite);
    CloseHandle(inf.hStdInRead);
    CloseHandle(inf.hStdInWrite);
    CloseHandle(inf.hStdOutRead);
    CloseHandle(inf.hStdOutWrite);
    return 1;
}