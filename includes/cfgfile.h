/*
cfgfile.h
������ȡ�����ļ����༰��Ա��������
*/
#pragma once

#include<string>
#include<Windows.h>
#include"serverparser.h"
#include"globalsettings.h"
#include"tinyxml2-8.0.0/tinystr.h"  
#include"tinyxml2-8.0.0/tinyxml.h"

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

