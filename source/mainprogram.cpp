#include"SysInit.h"
#include"logsys.h"
#include"cfgfile.h"
Settings set;

int main(int argc, char* argv) {
	WelcomeMessage();
	Initialize();
	string strUserInput;
	for (;;)
	{
		cin >> strUserInput;
		if (strUserInput == set.GetString(insprefix) + " stop")
		{
			//exit
		}
		
		//cout << strUserInput << endl;
	}
	cout << endl;
	return Finalize();
}