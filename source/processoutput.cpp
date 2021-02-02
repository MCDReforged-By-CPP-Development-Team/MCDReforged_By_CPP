#include "processoutput.h"

int stdfuncallconv ProcessServerOutput::ProcessOutput(LPSTR output, int reserved)
{
	OutputInterface serveroutput;
	serveroutput.Output(output, "Server", INFO_COMMONMSG);
	return 0;
}

int stdfuncallconv ProcessServerOutput::CannotProcessOutput()
{
	return 0;
}


