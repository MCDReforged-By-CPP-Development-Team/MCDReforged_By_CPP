#include "processoutput.h"

OutputInterface serveroutput;

int stdfuncallconv ProcessServerOutput::ProcessOutput(LPSTR output, int reserved)
{
    vector<string> splitedoutput = split(output, "\r\n");

    for (auto iter = splitedoutput.cbegin(); iter != splitedoutput.cend(); iter++) 
        serveroutput.Output((*iter).c_str(), "Server", INFO_COMMONMSG, S_STDOUT, true);

	return 0;
}

int stdfuncallconv ProcessServerOutput::CannotProcessOutput()
{
	return 0;
}
