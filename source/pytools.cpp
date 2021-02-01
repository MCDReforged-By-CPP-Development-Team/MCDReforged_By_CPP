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
	Sleep(1000);
	dp("pip");
	Sleep(1000);
	dp("pip");
	Sleep(1000);
	dp("pip");
	Sleep(1000);
	dp("pip");
	Sleep(1000);
	dp("pip");
	out.msg("Python�⣺" + Pylib + "��װ���");
	return 0;
}

