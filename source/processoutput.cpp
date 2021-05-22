#include "processoutput.h"

OutputInterface serveroutput;
Settings sett;
BaseParser* serverparser = NULL;

int stdfuncallconv ProcessServerOutput::ProcessOutput(LPSTR output, int reserved)
{
    vector<string> splitedoutput = split(output, "\r\n");
    int parser = sett.GetInt(parsertype);

    for (auto iter = splitedoutput.cbegin(); iter != splitedoutput.cend(); iter++) 
        serveroutput.Output((*iter).c_str(), "Server", INFO_COMMONMSG, S_STDOUT, true);

    switch (parser)
    {
    case VANILLA_PARSER_CODE:
        serverparser = new VanillaParser;
        break;
    case BUKKIT_PARSER_CODE:
        serverparser = new BukkitParser;
        break;
    case BUKKIT_14_PARSER_CODE:
        serverparser = new Bukkit14Parser;
        break;
    case BUNGEECORD_PARSER_CODE:
        serverparser = new BungeeCordParser;
        break;
    case CAT_SERVER_PARSER_CODE:
        serverparser = new CatParser;
        break;
    case WATERFALL_PARSER_CODE:
        serverparser = new WaterfallParser;
        break;
    case BETA18_PARSER_CODE:
        serverparser = new Beta18Parser;
        break;
    case FORGE_PARSER_CODE:
        serverparser = new ForgeParser;
        break;
    default:
        break;
    }

    //for (auto iter = splitedoutput.cbegin(); iter != splitedoutput.cend(); iter++) {
    //    serverparser->Parse(*iter);
    //}

	return 0;
}

int stdfuncallconv ProcessServerOutput::CannotProcessOutput()
{
	return -1;
}
