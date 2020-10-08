#pragma once

#include<regex>
#include<string>
#include<ctime>
#include<iostream>

#include"common.h"

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

struct Advancement;
struct PlayerMsg;
struct ServerParser;

int stdfuncallconv Parser(ServerParser* pResult, int parserCode, string rawText);
int stdfuncallconv VanillaParser(ServerParser* pResult, string rawText);
int stdfuncallconv BukkitParser(ServerParser* pResult, string rawText);
int stdfuncallconv Bukkit14Parser(ServerParser* pResult, string rawText);
int stdfuncallconv BungeeCordParser(ServerParser* pResult, string rawText);
int stdfuncallconv CatParser(ServerParser* pResult, string rawText);
int stdfuncallconv WaterfallParser(ServerParser* pResult, string rawText);
int stdfuncallconv ParserDebugPrint(string str);