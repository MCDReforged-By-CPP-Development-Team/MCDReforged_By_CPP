#include "pytools.h"

OutputInterface out;
string _Pylib_;//���ڸ��̴߳��ݲ���
//CMutex g_metux;
int ThreadMode = 0;
Pytools::Pytools(OutputInterface outt)
{
	out = outt;
}

int Pytools::InstallPyLibAsync(std::string Pylib) 
{
	_Pylib_ = Pylib;
	ThreadMode = INSTALL_PYLIB;
	Start();

	return 0;
}

void Pytools::Run()
{
	switch (ThreadMode)
	{
	case INSTALL_PYLIB:
		InstallPyLib(_Pylib_);
		break;
	default:
		break;
	}
	
}

int Pytools::InstallPyLib(std::string Pylib)
{
	//CLock lock(g_metux);

	dp(Pylib);
	out.msg("׼����װPython�⣺" + Pylib, "MCDRCPP");
	string cmd;
	cmd = "cmd.exe /C pip install " + Pylib;
	LPCSTR lpCmd = cmd.c_str();
	WinExec(lpCmd, SW_NORMAL);

	return 0;
}


