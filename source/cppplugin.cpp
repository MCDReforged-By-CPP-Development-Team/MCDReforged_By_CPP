#include "cppplugin.h"

vector<MCDRCPPPlugin> CppPluginList;
vector<MCDRCPPPluginConfigIns> CppPluginCfgList;

typedef MCDRCPPPluginInfo(*register_plugin_info)();
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

MCDRCPPPlugin::MCDRCPPPlugin(LPCSTR pluginPath)
{
	this->pluginPath = pluginPath;
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
	int iret;	
	ServerInterface si;
	if (plugin.cfgins.loadPlugin) {
		string path = plugin.pluginPath;
		plugin.pluginIns = LoadLibrary(path.c_str());

		if (plugin.pluginIns == NULL) return -1;

		funcptr_on_load onload;
		onload = (funcptr_on_load)GetProcAddress(plugin.pluginIns, FindListenerFuncRealName("on_load").c_str());

		iret = onload(si, plugin);
	}

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

	return " ";
}

