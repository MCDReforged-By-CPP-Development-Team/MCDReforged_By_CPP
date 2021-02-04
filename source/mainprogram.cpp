#include"SysInit.h"
#include"logsys.h"
#include"cfgfile.h"


int main(int argc, char* argv) {
	WelcomeMessage();
	Initialize();
	cout << endl;
	return Finalize();
}