#include"server.h"
RedirectInformation riInf;
ServerInterface::ServerInterface()
{
}

ServerInterface::~ServerInterface()
{
}

int stdfuncallconv ServerInterface::start(PREDIRECT_INFORMATION priInf)
{

	int openserverret = OpenServerAndRedirectIO(&riInf);
	riInf = *priInf;
	return openserverret;
}

int stdfuncallconv ServerInterface::stop()
{
	int iret = ProcessInput("stop");
	return iret;
}

int stdfuncallconv ServerInterface::restart()
{
	return 0;
}

int stdfuncallconv ServerInterface::wait_for_start()
{
	return 0;
}

int stdfuncallconv ServerInterface::stop_exit()
{
	return 0;
}

int stdfuncallconv ServerInterface::exit()
{
	return 0;
}
