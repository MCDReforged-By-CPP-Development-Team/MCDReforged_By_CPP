#include"redirectstdio.h"

int stdfuncallconv OpenServerAndRedirectIO(PREDIRECT_INFORMATION priInformation)
{

    HANDLE hStdInRead = NULL;   //�ӽ����õ�stdin�Ķ����  
    HANDLE hStdInWrite = NULL;  //�������õ�stdin�Ķ����  
    HANDLE hStdOutRead = NULL;  //�������õ�stdout�Ķ����  
    HANDLE hStdOutWrite = NULL; //�ӽ����õ�stdout��д���  
    HANDLE hStdErrWrite = NULL; //�ӽ����õ�stderr��д���  

    ProcessServerOutput output;
    DWORD process_exit_code;
	Settings sets;
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    SECURITY_ATTRIBUTES sa;

	string servercmdline = sets.GetString(servername);
	string jvmpath = sets.GetString(javapath);

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = true;
	sa.lpSecurityDescriptor = NULL;

    //����һ������stdin�Ĺܵ����õ�����HANDLE:  hStdInRead�����ӽ��̶������ݣ�hStdInWrite����������д������  
    //����sa��һ��STARTUPINFO�ṹ�壬�����CreatePipe����˵��  
    if (!CreatePipe(&hStdInRead, &hStdInWrite, &sa, 0))
        return -1;
    //����һ������stdout�Ĺܵ����õ�����HANDLE:  hStdInRead����������������ݣ�hStdInWrite�����ӳ���д������  
    if (!CreatePipe(&hStdOutRead, &hStdOutWrite, &sa, 0))
        return -1;

    //����һ������stdout�Ĺܵ����õ�����HANDLE:  hStdInRead����������������ݣ�hStdInWrite�����ӳ���д������  
    if (!CreatePipe(&hStdOutRead, &hStdOutWrite, &sa, 0))
        return -1;

    if (hStdInRead == NULL || hStdInWrite == NULL) return -1;
    if (hStdOutRead == NULL || hStdOutWrite == NULL) return -1;

    string startupcmd;// = "cmd.exe /C ";
    startupcmd.append(jvmpath).append(" ").append(servercmdline);

    LPSTR startcmd = new char[startupcmd.length() + 1];
    memset(startcmd, '\0', startupcmd.length() + 1);
    strcat_s(startcmd, startupcmd.length() + 1, startupcmd.c_str());
    dp(startcmd);

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags |= STARTF_USESHOWWINDOW;
    si.dwFlags |= STARTF_USESTDHANDLES;
    si.hStdOutput = hStdOutWrite;     //��˼�ǣ��ӽ��̵�stdout�����hStdOutWrite  
    si.hStdError = hStdErrWrite;        //��˼�ǣ��ӽ��̵�stderr�����hStdErrWrite  
    si.hStdInput = hStdInRead;
#ifdef DEBUG_FUNC_ENABLE
    si.wShowWindow = SW_SHOW;
#else
    si.wShowWindow = SW_HIDE;
#endif

    // STARTF_USESHOWWINDOW:The wShowWindow member contains additional information.
    // STARTF_USESTDHANDLES:The hStdInput, hStdOutput, and hStdError members contain additional information.
    // ��MSDN

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

    // �ȷ����ȡ�����ݿռ�
    DWORD dwTotalSize = NEWBUFFERSIZE;                     // �ܿռ�
    char* pchReadBuffer = new char[dwTotalSize];
    memset(pchReadBuffer, 0, NEWBUFFERSIZE);

    DWORD dwFreeSize = dwTotalSize;                 // ���ÿռ�

    dp("entering dowhile");
    do {
        if (FALSE == bSuc) {
            break;
        }

        // ���óɹ���־��֮��Ҫ�Ӷ�ȡ�Ƿ�ɹ�������
        bSuc = FALSE;

        char chTmpReadBuffer[NEWBUFFERSIZE] = { 0 };
        DWORD dwbytesRead = 0;

        // ���ڿ��ƶ�ȡƫ��
        OVERLAPPED Overlapped;
        memset(&Overlapped, 0, sizeof(OVERLAPPED));

        while (GetExitCodeProcess(pi.hProcess, &process_exit_code)) {
            
            // ��ջ���
            memset(chTmpReadBuffer, 0, NEWBUFFERSIZE);

            // ��ȡ�ܵ�
            BOOL bRead = ReadFile(hStdInRead, chTmpReadBuffer, NEWBUFFERSIZE, &dwbytesRead, &Overlapped);
            DWORD dwLastError = GetLastError();
            dp("dwLastError : " + dwLastError);

            if (bRead) {
                if (dwFreeSize >= dwbytesRead) {
                    // ���пռ��㹻������£�����ȡ����Ϣ������ʣ�µĿռ���
                    memcpy_s(pchReadBuffer + Overlapped.Offset, dwFreeSize, chTmpReadBuffer, dwbytesRead);
                    // ���¼����¿ռ�Ŀ��пռ�
                    dwFreeSize -= dwbytesRead;
                }
                else {
                    // ����Ҫ����Ŀռ��С
                    DWORD dwAddSize = (1 + dwbytesRead / NEWBUFFERSIZE) * NEWBUFFERSIZE;
                    // �����¿ռ��С
                    DWORD dwNewTotalSize = dwTotalSize + dwAddSize;
                    // �����¿ռ�Ŀ��д�С
                    dwFreeSize += dwAddSize;
                    // �·�����ʴ�С�Ŀռ�
                    char* pTempBuffer = new char[dwNewTotalSize];
                    // ����·���Ŀռ�
                    memset(pTempBuffer, 0, dwNewTotalSize);
                    // ��ԭ�ռ����ݿ�������
                    memcpy_s(pTempBuffer, dwNewTotalSize, pchReadBuffer, dwTotalSize);
                    // �����µĿռ��С
                    dwTotalSize = dwNewTotalSize;
                    // ����ȡ����Ϣ���浽�µĿռ���
                    memcpy_s(pTempBuffer + Overlapped.Offset, dwFreeSize, chTmpReadBuffer, dwbytesRead);
                    // ���¼����¿ռ�Ŀ��пռ�
                    dwFreeSize -= dwbytesRead;
                    // ��ԭ�ռ��ͷŵ�
                    delete[] pchReadBuffer;
                    // ��ԭ�ռ�ָ��ָ���¿ռ��ַ
                    pchReadBuffer = pTempBuffer;
                }

                // ��ȡ�ɹ����������ȡ������ƫ��
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
    inf.pi = pi;

    return bSuc;
}
//�˺������������ִ���Դ�� https://blog.csdn.net/breaksoftware/article/details/8595734 , https://blog.csdn.net/dicuzhaoqin8950/article/details/102229723 ͬʱ��л����

int WriteToPipe(HANDLE hWrite, char *in_buffer, DWORD dwSize) {
    DWORD dwWritten;
    int iRet = FALSE;

    //��WriteFile����hStdInWriteд�����ݣ�������in_buffer�У�����ΪdwSize  
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