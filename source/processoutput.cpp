#include "processoutput.h"
#include"serverparser.h"

OutputInterface serveroutput;
Settings sett;

int stdfuncallconv ProcessServerOutput::ProcessOutput(LPSTR output, int reserved)
{
    vector<string> splitedoutput = split(output, "\r\n");

    for (auto iter = splitedoutput.cbegin(); iter != splitedoutput.cend(); iter++) {
        serveroutput.Output((*iter).c_str(), "Server", INFO_COMMONMSG, S_STDOUT, true);
        ParseServerOutput(iter->c_str());
    }

	return 0;
}

int stdfuncallconv ProcessServerOutput::CannotProcessOutput()
{
	return -1;
}
