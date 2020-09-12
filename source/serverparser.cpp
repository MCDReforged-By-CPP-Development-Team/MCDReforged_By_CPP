#include"serverparser.h"

int stdfuncallconv Parser(pServerParser pResult, int parserCode, string rawText) {
	pServerParser resultTemp;
	int iRet = 0;

	switch (parserCode) {
	case VANILLA_PARSER_CODE:
		iRet = VanillaParser(resultTemp, rawText);
		break;

	case BUKKIT_PARSER_CODE:
		iRet = BukkitParser(resultTemp, rawText);
		break;

	case BUKKIT_14_PARSER_CODE:
		iRet = Bukkit14Parser(resultTemp, rawText);
		break;

	case BUNGEECORD_PARSER_CODE:
		iRet = BungeeCordParser(resultTemp, rawText);
		break;

	case CAT_SERVER_PARSER_CODE:
		iRet = CatParser(resultTemp, rawText);
		break;

	case WATERFALL_PARSER_CODE:
		iRet = WaterfallParser(resultTemp, rawText);
		break;

	}

	pResult->messageCate = resultTemp->messageCate;
	pResult->messageTime = resultTemp->messageTime;

	return iRet;
}

int stdfuncallconv VanillaParser(pServerParser pResult, string rawText) {
	regex regexDate("^[\\d+:\\d+:\\d+]");
	regex regexLoadupLower("^Done ([[1-9]\d*\.\d*|0\.\d*[1-9]\d*s)! For help, type \"help\"$");
	regex regexLoadupHigher("^Done ([1-9]\d*\.\d*|0\.\d*[1-9]\d*s)! For help, type \"help\" or \"?\"$");
	regex regexAdvan("^\\w{1,16} has made the advancement$");
	regex regexThreadState("^[\\w+/\\w+]");
	regex regexPlayer("^<\\w+>");
	regex regexPlayerLogin("^\\w+ joined the game");
	regex regexPlayerLogout("^\\w+ left the game");
	regex regexPlayerMessage("^<\\w+>\\w*$");

	cmatch match;

	bool ret = regex_search(rawText.c_str(), match, regexDate);
	string matchStr = match.str(1);
	ParserDebugPrint("Time::" + match.str(1));
	rawText.replace(0, matchStr.size(), "");

	ret = regex_search(rawText.c_str(), match, regexThreadState);
	ParserDebugPrint("Thread&State:" + match.str(1));
	matchStr = match.str(1);
	size_t index = matchStr.find("/");

	pResult->messager = matchStr.substr(1, index);
	ParserDebugPrint("messager:" + pResult->messager);

	pResult->status = matchStr.substr(index, matchStr.size() - 1);
	ParserDebugPrint("status:" + pResult->status);
	rawText.replace(0, matchStr.size(), "");

	ret = regex_search(rawText.c_str(), match, regexPlayer);

	if (!ret) {
		ret = regex_match(rawText.c_str(), match, regexPlayerMessage);
		if (!ret) {
			ret = regex_match(rawText.c_str(), match, regexAdvan);
			string matchStr = match.str(0);
			ParserDebugPrint("Advancement:" + match.str(1));
			if (!ret) {
				ret = regex_match(rawText.c_str(), match, regexLoadupLower);
				string matchStr = match.str(0);
				ParserDebugPrint("LoadupLower:" + match.str(1));
				if (!ret) {
					ret = regex_match(rawText.c_str(), match, regexLoadupHigher);
					string matchStr = match.str(0);
					ParserDebugPrint("LoadupHigher:" + match.str(1));
					if (!ret) {
						ret = regex_match(rawText.c_str(), match, regexPlayerLogin);
						if (!ret) {

						}
						else {
							regex_match(rawText.c_str(), match, regexPlayer);
							pResult->MajorMessage.playerName = match.str(1);
						}
					}
					else {
						regex_match(rawText.c_str(), match, regexPlayer);
						index = rawText.find(match.str(1));
						rawText.replace(0, matchStr.size(), "");
						pResult->MajorMessage.playerMessage = rawText;
					}
				}
				else {
					regex_match(rawText.c_str(), match, regexPlayer);
					index = rawText.find(match.str(1));
					rawText.replace(0, matchStr.size(), "");
					pResult->MajorMessage.playerMessage = rawText;
				}
			}
			else {
				index = rawText.find(match.str(1));
				rawText.replace(0, matchStr.size(), "");
				pResult->MajorMessage.advancement = rawText;
			}
		}
		else {
			index = rawText.find(match.str(1));
			rawText.replace(0, matchStr.size(), "");
			pResult->MajorMessage.playerMessage = rawText;
		}
	}
	else {

	}

	return 0;
}

int stdfuncallconv BukkitParser(pServerParser pResult, string rawText) {
	return 0;
}

int stdfuncallconv Bukkit14Parser(pServerParser pResult, string rawText) {
	return 0;
}

int stdfuncallconv BungeeCordParser(pServerParser pResult, string rawText) {
	return 0;
}

int stdfuncallconv CatParser(pServerParser pResult, string rawText) {
	return 0;
}

int stdfuncallconv WaterfallParser(pServerParser pResult, string rawText) {
	return 0;
}