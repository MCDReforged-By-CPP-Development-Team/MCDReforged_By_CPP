#include"processinput.h"
#include"cmdsys.h"

int stdfuncallconv ProcessInput(LPCSTR rawText)
{
	dp("Enter ProcessInput!");
	Settings GlobalSettings;
	string prefix = GlobalSettings.GetString(insprefix);
	dp(prefix);
	dp(rawText);

	string input = rawText;

	if (input.find_first_of(prefix) == 0) {	//区分MCDRCPP指令和发送给服务器的指令

	}
	else if(input.find_first_of("/") == 0){
		WriteToPipe(input.c_str(), input.length());
	}
	else {

	}

	return 0;
}
