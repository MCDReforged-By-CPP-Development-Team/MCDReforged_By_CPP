/*
cfgfile.h
包含读取配置文件的类及成员函数声明
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