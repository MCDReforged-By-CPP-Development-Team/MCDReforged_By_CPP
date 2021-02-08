#include "cppplugin.h"

vector<MCDRCPPPlugin> CppPluginList;

int stdfuncallconv MCDRCPPPlugin::Load()
{
	return 0;
}

int stdfuncallconv MCDRCPPPlugin::Remove()
{
	return 0;
}

MCDRCPPPlugin::MCDRCPPPlugin(LPCSTR pluginPath)
{
}

MCDRCPPPlugin::~MCDRCPPPlugin()
{
}

int stdfuncallconv GeneratePluginList()
{
	return 0;
}

int stdfuncallconv LoadPlugin(LPCSTR pluginName)
{
	return 0;
}

int stdfuncallconv LoadAllPlugins()
{
	return 0;
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
