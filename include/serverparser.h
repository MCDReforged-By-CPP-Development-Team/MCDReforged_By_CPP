#pragma once

#include<regex>
#include<string>
#include<ctime>
#include<iostream>

#include"globaldef.h"
#include"debugprint.h"
#include"utils.h"

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
struct Info;

class BaseParser {
public:
	virtual int stdfuncallconv Parse(string rawText) = 0;
	virtual ~BaseParser();
};

class VanillaParser :public BaseParser {
public:
	int stdfuncallconv Parse(string rawText);
};

class BukkitParser :public BaseParser {
public:
	int stdfuncallconv Parse(string rawText);
};

class Bukkit14Parser :public VanillaParser {
public:
	int stdfuncallconv Parse(string rawText);
};

class BungeeCordParser :public BaseParser {
public:
	int stdfuncallconv Parse(string rawText);
};

class CatParser :public BaseParser {
public:
	int stdfuncallconv Parse(string rawText);
};

class WaterfallParser :public BaseParser {
public:
	int stdfuncallconv Parse(string rawText);
};

class Beta18Parser :public BaseParser {
public:
	int stdfuncallconv Parse(string rawText);
};

class ForgeParser :public BaseParser {
public:
	int stdfuncallconv Parse(string rawText);
};