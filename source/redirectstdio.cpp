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
    si.hStdError = hStdIn;            // �Ѵ������̵ı�׼��������ض��򵽹ܵ�����
    si.hStdOutput = hStdIn;           // �Ѵ������̵ı�׼����ض��򵽹ܵ�����
#ifdef DEBUG_FUNC_ENABLE
    si.wShowWindow = SW_SHOW;
    #else
    si.wShowWindow = SW_HIDE;
#endif
    // STARTF_USESHOWWINDOW:The wShowWindow member contains additional information.
    // STARTF_USESTDHANDLES:The hStdInput, hStdOutput, and hStdError members contain additional information.
    // ��MSDN
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

    PROCESS_INFORMATION pi;

    BOOL bSuc = CreateProcess(NULL, startcmd, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi);
    
    if (bSuc == FALSE) { 
        dp("CreateProcess() Failed!");
        return -1;
    }

    // �ȷ����ȡ�����ݿռ�
    DWORD dwTotalSize = NEWBUFFERSIZE;                     // �ܿռ�
    char* pchReadBuffer = new char[dwTotalSize];
    memset(pchReadBuffer, 0, NEWBUFFERSIZE);

    DWORD dwFreeSize = dwTotalSize;                 // ���ÿռ�

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
            BOOL bRead = ReadFile(hStdIn, chTmpReadBuffer, NEWBUFFERSIZE, &dwbytesRead, &Overlapped);
            DWORD dwLastError = GetLastError();

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
//�˺������ִ���Դ�� https://blog.csdn.net/breaksoftware/article/details/8595734 ͬʱ��л����