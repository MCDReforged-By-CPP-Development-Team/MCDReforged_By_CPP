#include "processoutput.h"

int stdfuncallconv ProcessServerOutput::ProcessOutput(LPSTR output, int reserved)
{
	dp(output);
	return 0;
}

int stdfuncallconv ProcessServerOutput::CannotProcessOutput()
{
	return 0;
}


