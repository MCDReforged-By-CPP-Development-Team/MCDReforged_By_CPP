#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<Windows.h>
#include<guiddef.h>

#include"globaldef.h"
#include"utils.h"
#include"cfgfile.h"
#include"serverparser.h"
#include"server.h"
#include"debugprint.h"

#include"tinyxml2-8.0.0/tinystr.h"  
#include"tinyxml2-8.0.0/tinyxml.h"

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
	string pluginVersion;
	HINSTANCE pluginIns;
	MCDRCPPPlugin(LPCSTR pluginPath);
	~MCDRCPPPlugin();
private:
	bool isLoaded;
	//eventlistener”√∫Ø ˝÷∏’Î
};

struct MCDRCPPPluginInfo {
	GUID pluginGuid;
	string pluginName;
	string pluginVersion;
};

struct MCDRCPPPluginConfigIns {
	GUID pluginGuid;

	string pluginName;
	string pluginVersion;

	vector<string> listenerFuncNames;
	
	bool loadPlugin;
	bool dependency;
};

typedef MCDRCPPPluginInfo(*register_plugin_info)();
typedef int(*funcptr_on_load)(ServerInterface server_interface, MCDRCPPPlugin prev_module);
typedef int(*funcptr_on_remove)(ServerInterface server_interface);
typedef int(*funcptr_on_info)(ServerInterface server_interface, Info info);
typedef int(*funcptr_on_user_info)(ServerInterface server_interface, Info info);
typedef int(*funcptr_server_start)(ServerInterface server_interface);
typedef int(*funcptr_server_startup)(ServerInterface server_interface);
typedef int(*funcptr_server_stop)(ServerInterface server_interface, int server_return_code);
typedef int(*funcptr_mcdrcpp_start)(ServerInterface server_interface);
typedef int(*funcptr_mcdrcpp_stop)(ServerInterface server_interface);
typedef int(*funcptr_on_player_join)(ServerInterface server_interface, string player, Info info);
typedef int(*funcptr_on_player_left)(ServerInterface server_interface, string player);

int stdfuncallconv GeneratePluginList();
int stdfuncallconv LoadPlugin(MCDRCPPPlugin plugin);
int stdfuncallconv LoadAllPlugins();
int stdfuncallconv RemovePlugin(LPCSTR pluginName);
int stdfuncallconv RemoveAllPlugins();
int stdfuncallconv GetPluginInfo(LPCSTR pluginName);
int stdfuncallconv ReadPluginCfg(MCDRCPPPlugin plugin);
/*
<?xml version="1.0" encoding="UTF-8"?>
<CppPluginConfig>
	<Dependency></Dependency>
	<LoadPlugin></LoadPlugin>
	<PluginName></PluginName>
	<PluginUUID></PluginUUID>
	<PluginVersion>0.0.2</PluginVersion>
	<EventListenerFuncName Version="0.0.1">
		<on_load>OnLoad</on_load>
		...
	</EvenrListenerFuncName>
	<EventListenerFuncName Version="0.0.2">
		<on_load>OnLoad</on_load>
		...
	</EvenrListenerFuncName>
	<RegisterCommands>
		...
	</RegisterCommands>
</CppPluginConfig>
*/

bool stdfuncallconv GetNodePointerByName(TiXmlElement* pRootEle, const char* strNodeName, TiXmlElement*& Node);