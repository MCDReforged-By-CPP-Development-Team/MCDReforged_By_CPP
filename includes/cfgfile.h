/*
cfgfile.h
������ȡ�����ļ����༰��Ա��������
*/

#include<string>

using namespace std;

class LoadConfig {
private:
	static int ReadCfgFile(string cfgFilePath);
	static int CreateCfgFile();
	static bool ConfigFileExisting();
public:
	static int LoadConfigFile();
};