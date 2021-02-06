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
#define BETA18_PARSER_CODE 6
#define FORGE_PARSER_CODE 7

#pragma endregion

using namespace std;

struct Advancement;
struct PlayerMsg;
struct ServerParser;

class BaseParser {
public:
	virtual int stdfuncallconv Parse(string rawText, ServerParser* pResult) = 0;
	virtual ~BaseParser();
};

class VanillaParser :public BaseParser {
public:
	int stdfuncallconv Parse(string rawText, ServerParser* pResult);
};

class BukkitParser :public BaseParser {
public:
	int stdfuncallconv Parse(string rawText, ServerParser* pResult);
};

class Bukkit14Parser :public VanillaParser {
public:
	int stdfuncallconv Parse(string rawText, ServerParser* pResult);
};

class BungeeCordParser :public BaseParser {
public:
	int stdfuncallconv Parse(string rawText, ServerParser* pResult);
};

class CatParser :public BaseParser {
public:
	int stdfuncallconv Parse(string rawText, ServerParser* pResult);
};

class WaterfallParser :public BaseParser {
public:
	int stdfuncallconv Parse(string rawText, ServerParser* pResult);
};

class Beta18Parser :public BaseParser {
public:
	int stdfuncallconv Parse(string rawText, ServerParser* pResult);
};

class ForgeParser :public BaseParser {
public:
	int stdfuncallconv Parse(string rawText, ServerParser* pResult);
};