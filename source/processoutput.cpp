#include "processoutput.h"

OutputInterface serveroutput;

int stdfuncallconv ProcessServerOutput::ProcessOutput(LPSTR output, int reserved)
{
    vector<string> splitedoutput = split(output, "\r\n");

    for (auto iter = splitedoutput.cbegin(); iter != splitedoutput.cend(); iter++) 
        serveroutput.Output((*iter).c_str(), "Server", INFO_COMMONMSG, S_STDOUT, false);

	return 0;
}

int stdfuncallconv ProcessServerOutput::CannotProcessOutput()
{
	return 0;
}

vector<string> stdfuncallconv split(const string& str, const string& pattern)
{
    //const char* convert to char*
    char* strc = new char[strlen(str.c_str()) + 1];
    strcpy(strc, str.c_str());
    vector<string> resultVec;
    char* tmpStr = strtok(strc, pattern.c_str());
    while (tmpStr != NULL)
    {
        resultVec.push_back(string(tmpStr));
        tmpStr = strtok(NULL, pattern.c_str());
    }

    delete[] strc;

    return resultVec;
}   //来自 https://www.cnblogs.com/stonebloom-yu/p/6542756.html 感谢作者