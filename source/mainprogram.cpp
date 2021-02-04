#include"SysInit.h"
#include"logsys.h"
#include"cfgfile.h"


int main(int argc, char* argv) {
	WelcomeMessage();
	Initialize();
	string strUserInput;
	for (;;)
	{
		cin >> strUserInput;
		cout << strUserInput << endl;
	}
	cout << endl;
	return Finalize();
}