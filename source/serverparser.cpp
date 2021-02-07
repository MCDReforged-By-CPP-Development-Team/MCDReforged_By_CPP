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

int stdfuncallconv VanillaParser::Parse(string rawText, ServerParser* pResult)
{
	//[hh:mm:ss] [thread/cate]: [sender]content
	regex time("\[\d{2,}:\d{2,}:\d{2,}\]");	//[hh:mm:ss]
	regex info("\[[(0-9)(a-z)(A-Z)(_)\s]+/\w+\]");	//[thread/cate]
	regex sender("\[\w+\]");	//[sender]
	regex content(".*");	//content
	smatch m;
	bool found;

	dp(rawText);
	try
	{
		found = regex_search(rawText, m, time);
		dp(m.str(0));
	}
	catch (const std::exception&)
	{
		cout << "Failed while Parsing text:";
		cout << rawText.c_str() << endl;
	}
	return 0;
}

BaseParser::~BaseParser()
{
}

int stdfuncallconv BukkitParser::Parse(string rawText, ServerParser* pResult)
{
	return 0;
}

int stdfuncallconv Bukkit14Parser::Parse(string rawText, ServerParser* pResult)
{
	return 0;
}

int stdfuncallconv BungeeCordParser::Parse(string rawText, ServerParser* pResult)
{
	return 0;
}

int stdfuncallconv CatParser::Parse(string rawText, ServerParser* pResult)
{
	return 0;
}

int stdfuncallconv WaterfallParser::Parse(string rawText, ServerParser* pResult)
{
	return 0;
}

int stdfuncallconv Beta18Parser::Parse(string rawText, ServerParser* pResult)
{
	return 0;
}

int stdfuncallconv ForgeParser::Parse(string rawText, ServerParser* pResult)
{
	return 0;
}
