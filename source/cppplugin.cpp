#include "cppplugin.h"

vector<MCDRCPPPlugin> CppPluginList;
vector<MCDRCPPPluginConfigIns> CppPluginCfgList;

typedef MCDRCPPPluginInfo(*funcptr_register_plugin_info)();
typedef int(*funcptr_on_load) (ServerInterface server_interface, MCDRCPPPlugin prev_module);
typedef int(*funcptr_on_remove) (ServerInterface server_interface);
typedef int(*funcptr_on_info) (ServerInterface server_interface, Info info);
typedef int(*funcptr_on_user_info) (ServerInterface server_interface, Info info);
typedef int(*funcptr_server_start) (ServerInterface server_interface);
typedef int(*funcptr_server_startup) (ServerInterface server_interface);
typedef int(*funcptr_server_stop) (ServerInterface server_interface, int server_return_code);
typedef int(*funcptr_mcdrcpp_start) (ServerInterface server_interface);
typedef int(*funcptr_mcdrcpp_stop) (ServerInterface server_interface);
typedef int(*funcptr_on_player_join) (ServerInterface server_interface, string player, Info info);
typedef int(*funcptr_on_player_left) (ServerInterface server_interface, string player);

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

int stdfuncallconv LoadPlugin(MCDRCPPPlugin plugin, PMCDRCPPPlugin outplu)
{
	int iret;	
	ServerInterface si;
	if (plugin.cfgins.loadPlugin) {
		string path = plugin.pluginPath;
		plugin.pluginIns = LoadLibrary(path.c_str());

		if (plugin.pluginIns == NULL) return -1;

		funcptr_on_load fp_onload;
		fp_onload = (funcptr_on_load)GetProcAddress(plugin.pluginIns, FindListenerFuncRealName("on_load").c_str());

		iret = fp_onload(si, plugin);

		MCDRCPPPluginInfo reginfo;
		funcptr_register_plugin_info fp_regplugininfo;
		reginfo = fp_regplugininfo();
		(plugin).info = reginfo;
		plugin.info = reginfo;

		if (plugin.info.pluginGuid != plugin.cfgins.pluginGuid) plugin.pluginGuid = plugin.cfgins.pluginGuid; 
		else plugin.pluginGuid = plugin.info.pluginGuid;

		if (plugin.info.pluginName != plugin.cfgins.pluginName) plugin.pluginName = plugin.cfgins.pluginName;
		else plugin.pluginName = plugin.info.pluginName;

		if (plugin.info.pluginVersion != plugin.cfgins.pluginVersion) plugin.pluginVersion = plugin.cfgins.pluginVersion;
		else plugin.pluginVersion = plugin.info.pluginVersion;

		*outplu = plugin;
	}

	return 0;
}

int stdfuncallconv LoadAllPlugins()
{
	int iret;
	vector<MCDRCPPPlugin>::iterator iter;
	MCDRCPPPlugin plu;

	for (iter = CppPluginList.begin(); iter != CppPluginList.end(); iter++) {
		iret = LoadPlugin(*iter, &plu);
		CppPluginList.erase(iter);
		CppPluginList.insert(iter - 1, plu);
	}
	return iret;
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
	Settings cppset;
	MCDRCPPPluginConfigIns cfgins;

	string pluginPaths = cppset.GetString(cpppluginpath);
	string temp;

	vector<string> splitedpluginpath = split(pluginPaths, ";");
	vector<string> cfgfiles;
	vector<string> tempvec;
	vector<string>::iterator iter, tempiter;

	int iret = 0;

	for (iter = splitedpluginpath.begin(); iter != splitedpluginpath.end(); iter++) {
		tempvec = ListFiles(*iter, ".xml");
		for (tempiter = tempvec.begin(); tempiter != tempvec.end(); tempiter++) {
			temp = iter->append(*tempiter);
			cfgfiles.push_back(temp);
		}
	}

	for (iter = cfgfiles.begin(); iter != cfgfiles.end(); iter++) {
		dp(iter->append("[Current Plugin Config]"));
		TiXmlDocument Doc(iter->c_str());

		bool bret = Doc.LoadFile(TIXML_ENCODING_UTF8);
		string tinyxmlerror = ("ErrorID:" + Doc.ErrorId());
		tinyxmlerror += "ErrorDesc:";
		tinyxmlerror += Doc.ErrorDesc();
		if (!bret) {
			dp("Doc.LoadFile() failed.");
			dp(tinyxmlerror);
			return -1;
		}
		dp("Load Config File Successful.");
		TiXmlElement* pRootEle = Doc.RootElement();
		if (pRootEle == NULL) {
			dp("Doc.RootElement(); failed.");
			return -1;
		}
		dp("Get XML Root Element Successful.");

		TiXmlElement* pElem = NULL;

		GetNodePointerByName(pRootEle, "PluginUUID", pElem);
		if (pElem == NULL) {
			iret--;
			continue;
		}
		string mbguid = pElem->GetText();
		WCHAR* wcguid;
		mbtowc(wcguid, mbguid.c_str(), mbguid.length());
		auto ret = CLSIDFromString(wcguid, &(cfgins.pluginGuid));
		if (ret != NOERROR) {
			iret--;
			continue;
		}

		GetNodePointerByName(pRootEle, "Dependency", pElem);
		if (pElem == NULL) {
			iret--;
			continue;
		}
		int comver = CompareVersion(pElem->GetText(), MCDRCPP_VER);
		if (comver == -1) {
			iret--;
			cfgins.dependency = false;
			continue;
		}
		cfgins.dependency = true;

		GetNodePointerByName(pRootEle, "LoadPlugin", pElem);
		if (pElem == NULL) {
			iret--;
			continue;
		}
		temp = pElem->GetText();
		transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
		if (temp == "TRUE") cfgins.loadPlugin = true;
		else if (temp == "FALSE") cfgins.loadPlugin = false;
		else cfgins.loadPlugin = true;

		GetNodePointerByName(pRootEle, "PluginName", pElem);
		if (pElem == NULL) {
			iret--;
			continue;
		}
		cfgins.pluginName = pElem->GetText();

		GetNodePointerByName(pRootEle, "PluginVersion", pElem);
		if (pElem == NULL) {
			iret--;
			continue;
		}
		cfgins.pluginVersion = pElem->GetText();
		temp = cfgins.pluginVersion;

		GetNodePointerByName(pRootEle, "EventListenerFuncName", pElem);
		TiXmlElement* tempElem = new TiXmlElement(*pElem);


		for (; tempElem != NULL; tempElem = tempElem->NextSiblingElement()) {
			TiXmlAttribute* attribute = tempElem->FirstAttribute(); 
			if (cfgins.pluginVersion == attribute->Value()) {
				for (TiXmlNode* tempNode = tempElem->FirstChild()
					; tempNode != NULL
					; tempNode = tempNode->NextSibling()) {
					ListenerFunc templf;
					templf.ListenerFuncName = tempNode->ToElement()->Value();
					templf.RealFuncName = tempNode->ToElement()->GetText();
					cfgins.listenerFuncNames.push_back(templf);
				}
				break;
			}
		}

		CppPluginCfgList.push_back(cfgins);
		ZeroMemory(&cfgins, sizeof(MCDRCPPPluginConfigIns));
	}

	for (vector<MCDRCPPPlugin>::iterator pluginlistiter = CppPluginList.begin()
		; pluginlistiter != CppPluginList.end()
		; pluginlistiter++) {
		for (vector<MCDRCPPPluginConfigIns>::iterator plugincfglistiter = CppPluginCfgList.begin()
			; plugincfglistiter != CppPluginCfgList.end()
			; plugincfglistiter++) {
			if (pluginlistiter->pluginGuid == plugincfglistiter->pluginGuid) { 
				pluginlistiter->cfgins = *plugincfglistiter;
				break;
			}
		}
	}
	return 0;
}

string _fc FindListenerFuncRealName(LPCSTR funcName)
{
	vector<MCDRCPPPlugin>::iterator iter;
	vector<ListenerFunc>::iterator funcnameiter;

	for (iter = CppPluginList.begin(); iter != CppPluginList.end(); iter++) {
		for (funcnameiter = iter->cfgins.listenerFuncNames.begin(); funcnameiter != iter->cfgins.listenerFuncNames.end(); funcnameiter++) {
			if (funcnameiter->ListenerFuncName == funcName) return string(funcnameiter->RealFuncName);
		}
	}

	return "";
}

#pragma region con_de_op_func

MCDRCPPPluginInfo::MCDRCPPPluginInfo()
{

}
MCDRCPPPluginInfo::MCDRCPPPluginInfo(GUID guid, LPCSTR name, LPCSTR ver)
{

}
MCDRCPPPluginInfo::MCDRCPPPluginInfo(PMCDRCPPPluginInfo)
{

}
void MCDRCPPPluginInfo::operator=(MCDRCPPPluginInfo b)
{
	this->pluginGuid = b.pluginGuid;
	this->pluginName = b.pluginName;
	this->pluginVersion = b.pluginVersion;
}

MCDRCPPPlugin::MCDRCPPPlugin(LPCSTR pluginPath)
{
	this->pluginPath = pluginPath;
	this->pluginName = "";
	this->pluginVersion = "";
	this->isLoaded = false;
	this->pluginIns = NULL;

	GUID guid;
	ZeroMemory(&guid, sizeof(GUID));
	this->pluginGuid = guid;
}
MCDRCPPPlugin::MCDRCPPPlugin(PMCDRCPPPlugin plugin)
{

}
MCDRCPPPlugin::MCDRCPPPlugin()
{
	this->pluginPath = "";
	this->pluginName = "";
	this->pluginVersion = "";
	this->isLoaded = false;
	this->pluginIns = NULL;

	GUID guid;
	ZeroMemory(&guid, sizeof(GUID));
	this->pluginGuid = guid;
}
MCDRCPPPlugin::~MCDRCPPPlugin()
{
	CloseHandle(this->pluginIns);
}
void MCDRCPPPlugin::operator=(MCDRCPPPlugin b)
{

}

ListenerFunc::ListenerFunc()
{

}
ListenerFunc::ListenerFunc(LPCSTR listener, LPCSTR real)
{

}
ListenerFunc::ListenerFunc(PListenerFunc)
{

}
void ListenerFunc::operator=(ListenerFunc b)
{

}

MCDRCPPPluginConfigIns::MCDRCPPPluginConfigIns()
{

}
MCDRCPPPluginConfigIns::MCDRCPPPluginConfigIns(PListenerFunc)
{

}
void MCDRCPPPluginConfigIns::operator=(MCDRCPPPluginConfigIns b)
{

}

#pragma endregion
