#pragma once

#include<regex>
#include<string>
#include<ctime>
#include<iostream>

#include"common.h"
#include"debugprint.h"

#pragma region Marcos

#define VANILLA_PARSER_CODE 0
#define BUKKIT_PARSER_CODE 1
#define BUKKIT_14_PARSER_CODE 2
#define BUNGEECORD_PARSER_CODE 3
#define CAT_SERVER_PARSER_CODE 4
#define WATERFALL_PARSER_CODE 5

#pragma endregion

using namespace std;

struct Advancement;
struct PlayerMsg;
struct ServerParser;

class BaseParser {
	virtual int stdfuncallconv Parser(ServerParser* pResult, int parserCode, string rawText) = 0;
	virtual int stdfuncallconv Parse(string rawText) = 0;
};

class VanillaParser :BaseParser {
	int stdfuncallconv Parser(ServerParser* pResult, int parserCode, string rawText);
	int stdfuncallconv Parse(string rawText);
};

class BukkitParser :BaseParser {
	int stdfuncallconv Parser(ServerParser* pResult, int parserCode, string rawText);
	int stdfuncallconv Parse(string rawText);
};

class Bukkit14Parser :VanillaParser {
	int stdfuncallconv Parser(ServerParser* pResult, int parserCode, string rawText);
	int stdfuncallconv Parse(string rawText);
};

class BungeeCordParser :BaseParser {
	int stdfuncallconv Parser(ServerParser* pResult, int parserCode, string rawText);
	int stdfuncallconv Parse(string rawText);
};

class CatParser :BaseParser {
	int stdfuncallconv Parser(ServerParser* pResult, int parserCode, string rawText);
	int stdfuncallconv Parse(string rawText);
};

class WaterfallParser :BaseParser {
	int stdfuncallconv Parser(ServerParser* pResult, int parserCode, string rawText);
	int stdfuncallconv Parse(string rawText);
};