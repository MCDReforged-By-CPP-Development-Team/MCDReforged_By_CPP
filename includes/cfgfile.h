/*
cfgfile.h
������ȡ�����ļ����༰��Ա��������
*/

#include<string>
#include<Windows.h>
#include "tinyxml2-8.0.0/tinystr.h"  
#include "tinyxml2-8.0.0/tinyxml.h"

using namespace std;

class LoadConfig {
private:
	static int ReadCfgFile(string cfgFilePath);
	static int CreateCfgFile();
	static bool ConfigFileExisting();
public:
	static int LoadConfigFile();
};