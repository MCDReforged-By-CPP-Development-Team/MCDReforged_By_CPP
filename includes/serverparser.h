#include<regex>
#include<string>
#include<ctime>
#include<iostream>

#define VANILLA_PARSER_CODE 0
#define BUKKIT_PARSER_CODE 1
#define BUKKIT_14_PARSER_CODE 2
#define BUNGEECORD_PARSER_CODE 3
#define CAT_SERVER_PARSER_CODE 4
#define WATERFALL_PARSER_CODE 5

using namespace std;

// [09:00:00] [Server thread/INFO]: <Steve> Hello
// [09:00:01] [Server thread/WARN]: Can't keep up!
// [Server thread/INFO]: <Steve> Hello
// [Server thread/WARN]: Can't keep up!
// <Steve> Hello
// Can't keep up!
// Steve has made the advancement [Stone Age]
// 1.13 + Done(3.500s)!For help, type "help"
// 1.13 - Done(3.500s)!For help, type "help" or "?"
// RCON running on 0.0.0.0:25575

struct Advancement {
	string playerName;
	string advancement;
};

struct PlayerMsg {
	string playerName;
	string playerMsg;
};

typedef struct _ServerParser {
	_ServerParser() {
		messageCate = 0;
		messageTime = { 0 };
	}
	~_ServerParser() { }
	tm messageTime;
	string status;
	int messageCate;
	union MajorMessage {
		MajorMessage() { }

		~MajorMessage() { }

		string playerName;
		Advancement advancement;
		int loadInTime;
		string rconRunningIpAndPort;
	}MajorMessage;
}ServerParser, *pServerParser;

int Parser(pServerParser pResult, int parserCode, string rawText);
int VanillaParser(pServerParser pResult, string rawText);
int BukkitParser(pServerParser pResult, string rawText);
int Bukkit14Parser(pServerParser pResult, string rawText);
int BungeeCordParser(pServerParser pResult, string rawText);
int CatParser(pServerParser pResult, string rawText);
int WaterfallParser(pServerParser pResult, string rawText);

int ParserDebugPrint(string str) {
	cout << "[ParserDebugPrint]" << str << endl;
}