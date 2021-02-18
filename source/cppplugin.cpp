#include "cppplugin.h"

vector<MCDRCPPPlugin> CppPluginList;
vector<MCDRCPPPluginConfigIns> CppPluginCfgList;

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
	string path = plugin.pluginPath;
	plugin.pluginIns = LoadLibrary(path.c_str());

	if (plugin.pluginIns == NULL) return -1;

	funcptr_on_load onload;
	onload = (funcptr_on_load)GetProcAddress(plugin.pluginIns, );
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

int stdfuncallconv ReadPluginCfg(MCDRCPPPlugin plugin)
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
		temp = pElem->GetText();
		transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
		if (temp == "TRUE") cfgins.loadPlugin = true;
		else if (temp == "FALSE") cfgins.loadPlugin = false;
		else cfgins.loadPlugin = true;

		GetNodePointerByName(pRootEle, "PluginName", pElem);
		cfgins.pluginName = pElem->GetText();
	}
	return 0;
}

bool stdfuncallconv GetNodePointerByName(TiXmlElement* pRootEle, const char* strNodeName, TiXmlElement*& Node)    //https://blog.csdn.net/masikkk/article/details/14191933?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.add_param_isCf&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.add_param_isCf
{
	if (0 == strcmp(strNodeName, pRootEle->Value()))
	{
		Node = pRootEle;
		return true;
	}

	TiXmlElement* pEle = pRootEle;
	for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement())
	{
		if (0 != strcmp(pEle->Value(), strNodeName))
		{
			GetNodePointerByName(pEle, strNodeName, Node);
		}
		else
		{
			Node = pEle;
			return true;
		}
	}

	return false;
}