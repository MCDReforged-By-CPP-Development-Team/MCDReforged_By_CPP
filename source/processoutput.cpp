#include "processoutput.h"

OutputInterface serveroutput;

int stdfuncallconv ProcessServerOutput::ProcessOutput(LPSTR output, int reserved)
{
	serveroutput.Output(output, "Server", INFO_COMMONMSG, S_STDOUT, false);
	return 0;
}

int stdfuncallconv ProcessServerOutput::CannotProcessOutput()
{
	return 0;
}


