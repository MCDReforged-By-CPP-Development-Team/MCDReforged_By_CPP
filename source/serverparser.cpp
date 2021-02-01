#include"serverparser.h"

struct PlayerMsg {
	string playerName;
	string playerMsg;
};

struct Advancement {
	string playerName;
	string advancement;

	void operator=(Advancement* in) {
		this->playerName = in->playerName;
		this->advancement = in->advancement;
	}
};

int stdfuncallconv VanillaParser::Parser(ServerParser* pResult, int parserCode, string rawText)
{
	return 0;
}

int stdfuncallconv VanillaParser::Parse(string rawText)
{
	return 0;
}
