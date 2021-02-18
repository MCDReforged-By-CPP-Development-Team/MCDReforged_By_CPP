#include"readmcdrconfig.h"
using namespace YAML;

int stdfuncallconv ReadMCDRConfig_0()
{
	Settings set;
	string tempstr1, tempstr2;
	int tempi;
	Node config = LoadFile("config.yml");

	if (config["language"].as<string>() == "zh_cn") {
		set.SetString(lang, "zh_CN");
	}
	else {
		set.SetString(lang, "en_US");
	}

	set.SetString(serverdir, config["working_directory"].as<string>());

	set.SetString(startcmd, config["start_command"].as<string>());

	tempstr1 = config["parser"].as<string>();
	if (tempstr1 == "vanilla_parser") tempi = VANILLA_PARSER_CODE;
	else if (tempstr1 == "beta18_parser") tempi = BETA18_PARSER_CODE;
	else if (tempstr1 == "bukkit_parser") tempi = BUKKIT_PARSER_CODE;
	else if (tempstr1 == "bukkit14_parser") tempi = BUKKIT_14_PARSER_CODE;
	else if (tempstr1 == "forge_parser") tempi = FORGE_PARSER_CODE;
	else if (tempstr1 == "cat_server_parser") tempi = CAT_SERVER_PARSER_CODE;
	else if (tempstr1 == "bungeecord_parser") tempi = BUNGEECORD_PARSER_CODE;
	else if (tempstr1 == "waterfall_parser") tempi = WATERFALL_PARSER_CODE;
	else tempi = VANILLA_PARSER_CODE;
	set.SetInt(parsertype, tempi);

	set.SetString(pypluginpath, config["plugin_directories"].as<string>());
	return 0;
}

int stdfuncallconv ReadMCDRConfig_1()
{
	Settings set;
	string tempstr1, tempstr2;
	int tempi;
	Node config = LoadFile("config.yml");
	
	if (config["language"].as<string>() == "zh_cn") {
		set.SetString(lang, "zh_CN");
	}
	else {
		set.SetString(lang, "en_US");
	}

	set.SetString(serverdir, config["working_directory"].as<string>());

	set.SetString(startcmd, config["start_command"].as<string>());

	tempstr1 = config["handler"].as<string>();
	if (tempstr1 == "vanilla_handler") tempi = VANILLA_PARSER_CODE;
	else if (tempstr1 == "beta18_handler") tempi = BETA18_PARSER_CODE;
	else if (tempstr1 == "bukkit_handler") tempi = BUKKIT_PARSER_CODE;
	else if (tempstr1 == "bukkit14_handler") tempi = BUKKIT_14_PARSER_CODE;
	else if (tempstr1 == "forge_handler") tempi = FORGE_PARSER_CODE;
	else if (tempstr1 == "cat_server_handler") tempi = CAT_SERVER_PARSER_CODE;
	else if (tempstr1 == "bungeecord_handler") tempi = BUNGEECORD_PARSER_CODE;
	else if (tempstr1 == "waterfall_handler") tempi = WATERFALL_PARSER_CODE;
	else tempi = VANILLA_PARSER_CODE;
	set.SetInt(parsertype, tempi);

	set.SetString(pypluginpath, config["plugin_directories"].as<string>());
	return 0;
}

int stdfuncallconv ReadMCDRPermission()
{
	Node config = LoadFile("config.yml");
	vector<string>::iterator iter;
	std::vector<string> owner = config["owner"].as<std::vector<string>>();
	std::vector<string> admin = config["admin"].as<std::vector<string>>();
	std::vector<string> helper = config["helper"].as<std::vector<string>>();
	std::vector<string> user = config["user"].as<std::vector<string>>();
	std::vector<string> guest = config["guest"].as<std::vector<string>>();
	Permission per;

	for (iter = owner.begin(); iter != owner.end(); iter++) per.SetUserPermission(iter->c_str(), PERMISSION_OWNER);
	for (iter = admin.begin(); iter != admin.end(); iter++) per.SetUserPermission(iter->c_str(), PERMISSION_ADMIN);
	for (iter = helper.begin(); iter != helper.end(); iter++) per.SetUserPermission(iter->c_str(), PERMISSION_HELPER);
	for (iter = user.begin(); iter != user.end(); iter++) per.SetUserPermission(iter->c_str(), PERMISSION_USER);
	for (iter = guest.begin(); iter != guest.end(); iter++) per.SetUserPermission(iter->c_str(), PERMISSION_GUEST);
	return 0;
}
