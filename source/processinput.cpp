#include"processinput.h"
#include"cmdsys.h"

int stdfuncallconv ProcessInput(LPCSTR rawText)
{
	dp("Enter ProcessInput!");
	Settings GlobalSettings;
	string prefix = GlobalSettings.GetString(insprefix);
	dp(prefix);
	dp(GlobalSettings.GetString(insprefix));
	dp(rawText);

	string input = rawText;

	if (input.find_first_of(prefix) == 0) {	//区分MCDRCPP指令和发送给服务器的指令
		dp("mcdr command");
		NewMCDRCommand(input);
	}
	else if(input.find_first_of("/") == 0){
		dp("minecraft command");
		int writeret = WriteToPipe(input.c_str(), input.length());
		if (writeret == FALSE) {
			dp("WriteToPipe() failed!");
			return -1;
		}
	}
	else {
		dp("unknown input type");
	}

	return 0;
}
