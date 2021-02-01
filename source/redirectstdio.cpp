#include"redirectstdio.h"



HANDLE hStdIn = NULL;
HANDLE hStdOut = NULL;
HANDLE hStdErr = NULL;

int stdfuncallconv OpenServerAndRedirectIO()
{
    ProcessServerOutput output;
    DWORD process_exit_code;
	Settings sets;
	string servercmdline = sets.GetString(servername);
	string jvmpath = sets.GetString(javapath);
	STARTUPINFO stinfo;
	memset(&stinfo, sizeof(STARTUPINFO), 0);
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = true;
	sa.lpSecurityDescriptor = NULL;

	if (CreatePipe(&hStdIn, &hStdOut, &sa, 0) == FALSE) return -1;
    if (hStdIn == NULL || hStdOut == NULL) return -1;

    string startupcmd = "cmd.exe /C ";
    startupcmd.append(jvmpath).append(" ").append(servercmdline);

    LPSTR startcmd = new char[startupcmd.length() + 1];
    memset(startcmd, '\0', startupcmd.length() + 1);
    strcat_s(startcmd, startupcmd.length() + 1, startupcmd.c_str());
    dp(startcmd);

    STARTUPINFO si;
    si.cb = sizeof(STARTUPINFO);
    GetStartupInfo(&si);
    si.hStdError = hStdIn;            // 把创建进程的标准错误输出重定向到管道输入
    si.hStdOutput = hStdIn;           // 把创建进程的标准输出重定向到管道输入
#ifdef DEBUG_FUNC_ENABLE
    si.wShowWindow = SW_SHOW;
    #else
    si.wShowWindow = SW_HIDE;
#endif
    // STARTF_USESHOWWINDOW:The wShowWindow member contains additional information.
    // STARTF_USESTDHANDLES:The hStdInput, hStdOutput, and hStdError members contain additional information.
    // 自MSDN
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

    PROCESS_INFORMATION pi;

    BOOL bSuc = CreateProcess(NULL, startcmd, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi);
    
    if (bSuc == FALSE) { 
        dp("CreateProcess() Failed!");
        return -1;
    }

    // 先分配读取的数据空间
    DWORD dwTotalSize = NEWBUFFERSIZE;                     // 总空间
    char* pchReadBuffer = new char[dwTotalSize];
    memset(pchReadBuffer, 0, NEWBUFFERSIZE);

    DWORD dwFreeSize = dwTotalSize;                 // 闲置空间

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
            BOOL bRead = ReadFile(hStdIn, chTmpReadBuffer, NEWBUFFERSIZE, &dwbytesRead, &Overlapped);
            DWORD dwLastError = GetLastError();

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

    if (NULL != hStdIn) {
        CloseHandle(hStdIn);
        hStdIn = NULL;
    }

    WaitForSingleObject(pi.hProcess, INFINITE); //wait for server exit

    delete[] pchReadBuffer;
    delete[] startcmd;
    startcmd = NULL;
    pchReadBuffer = NULL;
    CloseHandle(hStdErr);
    CloseHandle(hStdIn);
    CloseHandle(hStdOut);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return bSuc;
}
//此函数部分代码源于 https://blog.csdn.net/breaksoftware/article/details/8595734 同时感谢作者