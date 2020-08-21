/*
cfgfile.h
������ȡ�����ļ����༰��Ա��������
*/

#include<string>
#include<Windows.h>
#include"tinyxml2-8.0.0/tinystr.h"  
#include"tinyxml2-8.0.0/tinyxml.h"
#include"globalsettings.h"
#include"serverparser.h"

using namespace std;

class LoadConfig {
private:
	static int ReadCfgFile(string cfgFilePath);
	static int CreateCfgFile();
	static bool ConfigFileExisting();
	static bool StringToBool(string Temp);
	static bool GetNodePointerByName(TiXmlElement* pRootEle, std::string& strNodeName, TiXmlElement*& Node);
	static int StringToParserCode(string parserName);
public:
	static int LoadConfigFile();
};