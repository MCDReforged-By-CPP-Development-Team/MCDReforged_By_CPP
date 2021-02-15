#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<Windows.h>
#include<guiddef.h>

#include"common.h"
#include"utils.h"
#include"cfgfile.h"
#include"redirectstdio.h"
#include"serverparser.h"

using namespace std;

/*
register_plugin_info
on_load on_remove on_info on_user_info server_start server_startup mcdr_start mcdr_stop on_player_join on_player_left
*/

class MCDRCPPPlugin {
public:
	GUID pluginGuid;
	string pluginName;
	string pluginPath;
	MCDRCPPPlugin(LPCSTR pluginPath);
	~MCDRCPPPlugin();
private:
	bool isLoaded;
	HANDLE pluginHandle;
	//eventlistener”√∫Ø ˝÷∏’Î
};

struct MCDRCPPPluginInfo {
	GUID pluginGuid;
	string pluginName;
};

typedef MCDRCPPPluginInfo(*register_plugin_info)();
typedef int(*on_load)(MCDRCPPPlugin prev_module);
typedef int(*on_remove)();
typedef int(*on_info)(Info info);
typedef int(*on_user_info)(Info info);
typedef int(*server_start)();
typedef int(*server_startup)();
typedef int(*server_stop)();
typedef int(*mcdrcpp_start)();
typedef int(*mcdrcpp_stop)();
typedef int(*on_player_join)(string player, Info info);
typedef int(*on_player_left)(string player, Info info);

int stdfuncallconv GeneratePluginList();
int stdfuncallconv LoadPlugin(MCDRCPPPlugin plugin);
int stdfuncallconv LoadAllPlugins();
int stdfuncallconv RemovePlugin(LPCSTR pluginName);
int stdfuncallconv RemoveAllPlugins();
int stdfuncallconv GetPluginInfo(LPCSTR pluginName);
int stdfuncallconv ReadPluginCfg();