#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<Windows.h>
#include<guiddef.h>

#include"common.h"
#include"utils.h"
#include"cfgfile.h"

using namespace std;

/*
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

int stdfuncallconv GeneratePluginList();
int stdfuncallconv LoadPlugin(MCDRCPPPlugin plugin);
int stdfuncallconv LoadAllPlugins();
int stdfuncallconv RemovePlugin(LPCSTR pluginName);
int stdfuncallconv RemoveAllPlugins();
int stdfuncallconv GetPluginInfo(LPCSTR pluginName);
int stdfuncallconv ReadPluginCfg();