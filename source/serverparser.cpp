#include"serverparser.h"

int Parser(pServerParser pResult, int parserCode, string rawText) {
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

int VanillaParser(pServerParser pResult, string rawText) {
	return 0;
}

int BukkitParser(pServerParser pResult, string rawText) {
	return 0;
}

int Bukkit14Parser(pServerParser pResult, string rawText) {
	return 0;
}

int BungeeCordParser(pServerParser pResult, string rawText) {
	return 0;
}

int CatParser(pServerParser pResult, string rawText) {
	return 0;
}

int WaterfallParser(pServerParser pResult, string rawText) {
	return 0;
}