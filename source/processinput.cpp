#include"processinput.h"
#include"cmdsys.h"

int stdfuncallconv ProcessInput(LPCSTR rawText)
{
	Settings GlobalSettings;
	string prefix = GlobalSettings.GetString(insprefix);

	string input = rawText;

	if (input.find_first_of(prefix) == 0) {	//区分MCDRCPP指令和发送给服务器的指令
		NewMCDRCommand(input);
	}
	else {
		int writeret = WriteToPipe(input.c_str(), input.length());
		if (writeret == FALSE) {
			dp("WriteToPipe() failed!");
			return -1;
		}
	}

	return 0;
}
