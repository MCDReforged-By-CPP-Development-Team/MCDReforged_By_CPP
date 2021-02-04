#pragma once

#ifndef __PYTOOLS__

#include "common.h"
#include "logsys.h"
#include "cthread.h"
#include <string>
#include <Windows.h>
#include <thread>
using namespace std;

#define INSTALL_PYLIB 0x01

class Pytools :public CThread
{

public:
	Pytools(OutputInterface outt);
	
	int stdfuncallconv InstallPyLibAsync(string Pylib);//安装Python库（多线程）

	virtual void Run();//(多线程用)不要调用这个函数！！！！！！！ DO NOT USE THIS FUNCTION!!!!!!!!!!!
	
private:               
	int stdfuncallconv InstallPyLib(string Pylib);
};




#endif // !__PYTOOLS__
