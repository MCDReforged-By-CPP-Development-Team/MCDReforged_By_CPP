#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<Windows.h>
#include<guiddef.h>
#include<algorithm>

#include"globaldef.h"
#include"utils.h"
#include"cfgfile.h"
#include"serverparser.h"
#include"server.h"
#include"debugprint.h"
#include"xmlfunc.h"

#include"tinyxml2-8.0.0/tinystr.h"  
#include"tinyxml2-8.0.0/tinyxml.h"

using namespace std;

/*
register_plugin_info
on_load on_remove on_info on_user_info server_start server_startup mcdr_start mcdr_stop on_player_join on_player_left
*/

struct ListenerFunc;
struct MCDRCPPPluginInfo;
struct MCDRCPPPluginConfigIns;
class MCDRCPPPlugin;

typedef ListenerFunc* PListenerFunc;
typedef MCDRCPPPluginInfo* PMCDRCPPPluginInfo;
typedef MCDRCPPPluginConfigIns* PMCDRCPPPluginConfigIns;
typedef MCDRCPPPlugin* PMCDRCPPPlugin;

struct ListenerFunc {
public:
	string ListenerFuncName;
	string RealFuncName;

	ListenerFunc();
	ListenerFunc(LPCSTR listener, LPCSTR real);
	ListenerFunc(PListenerFunc);

	void operator= (ListenerFunc b);
};

struct MCDRCPPPluginInfo {
public:
	GUID pluginGuid;
	string pluginName;
	string pluginVersion;

	MCDRCPPPluginInfo();
	MCDRCPPPluginInfo(GUID guid, LPCSTR name, LPCSTR ver);
	MCDRCPPPluginInfo(PMCDRCPPPluginInfo);

	void operator=(MCDRCPPPluginInfo b);
};

struct MCDRCPPPluginConfigIns {
public:
	GUID pluginGuid;

	string pluginName;
	string pluginVersion;

	vector<ListenerFunc> listenerFuncNames;

	bool loadPlugin;
	bool dependency;

	MCDRCPPPluginConfigIns();
	MCDRCPPPluginConfigIns(PListenerFunc);

	void operator= (MCDRCPPPluginConfigIns b);
};

class MCDRCPPPlugin {
public:
	GUID pluginGuid;
	bool isLoaded;
	string pluginName;
	string pluginPath;
	string pluginVersion;
	HINSTANCE pluginIns;

	MCDRCPPPluginConfigIns cfgins;
	MCDRCPPPluginInfo info;

	MCDRCPPPlugin(LPCSTR pluginPath);
	MCDRCPPPlugin(PMCDRCPPPlugin plugin);
	MCDRCPPPlugin();
	~MCDRCPPPlugin();

	void operator=(MCDRCPPPlugin b);
};

class MCDRCPPPluginIns {

};

int stdfuncallconv GeneratePluginList();
int stdfuncallconv LoadPlugin(MCDRCPPPlugin plugin, PMCDRCPPPlugin outplu);
int stdfuncallconv LoadAllPlugins();
int stdfuncallconv RemovePlugin(LPCSTR pluginName);
int stdfuncallconv RemoveAllPlugins();
int stdfuncallconv GetPluginInfo(LPCSTR pluginName);
int stdfuncallconv ReadPluginCfg();
string _fc FindListenerFuncRealName(LPCSTR funcName);

/*
<?xml version="1.0" encoding="UTF-8"?>
<CppPluginInfo>
	<Dependency></Dependency>
	<LoadPlugin></LoadPlugin>
	<PluginName></PluginName>
	<PluginUUID></PluginUUID>
	<PluginVersion>0.0.2</PluginVersion>
	<EventListenerFuncName Version="0.0.1">
		<on_load>OnLoad</on_load>
		...
	</EventListenerFuncName>
	<EventListenerFuncName Version="0.0.2">
		<on_load>OnLoad</on_load>
		...
	</EventListenerFuncName>
	<RegisterCommands>
		...
	</RegisterCommands>
</CppPluginInfo>
*/