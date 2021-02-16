#include "cppplugin.h"

vector<MCDRCPPPlugin> CppPluginList;

MCDRCPPPlugin::MCDRCPPPlugin(LPCSTR pluginPath)
{
	this->pluginPath = pluginPath;
	this->isLoaded = false;
	this->pluginHandle = NULL;

	GUID guid;
	ZeroMemory(&guid, sizeof(GUID));
	this->pluginGuid = guid;
}

MCDRCPPPlugin::~MCDRCPPPlugin()
{
	CloseHandle(this->pluginHandle);
}

int stdfuncallconv GeneratePluginList()
{
	Settings cppset;
	string pluginPaths = cppset.GetString(cpppluginpath);
	vector<string> splitedpluginpath = split(pluginPaths, ";");
	vector<string>::iterator iter, tempiter;

	for (iter = splitedpluginpath.begin(); iter != splitedpluginpath.end(); iter++) {
		vector<string> temp = ListFiles(*iter, ".dll");
		for (tempiter = temp.begin(); tempiter != temp.end(); tempiter++) {
			MCDRCPPPlugin plugintemp(tempiter->c_str());
			CppPluginList.push_back(plugintemp);
		}
	}
	return 0;
}

int stdfuncallconv LoadPlugin(MCDRCPPPlugin plugin)
{
	return 0;
}

int stdfuncallconv LoadAllPlugins()
{
	int iRet = 0;
	vector<MCDRCPPPlugin>::iterator iter;
	for (iter = CppPluginList.begin(); iter != CppPluginList.end(); iter++) {
		iRet = LoadPlugin(*iter);
	}
	return iRet;
}

int stdfuncallconv RemovePlugin(LPCSTR pluginName)
{
	return 0;
}

int stdfuncallconv RemoveAllPlugins()
{
	return 0;
}

int stdfuncallconv GetPluginInfo(LPCSTR pluginName)
{
	return 0;
}

int stdfuncallconv ReadPluginCfg()
{
	return 0;
}
