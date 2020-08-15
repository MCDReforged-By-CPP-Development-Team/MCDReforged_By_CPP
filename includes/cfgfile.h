/*
cfgfile.h
包含读取配置文件的类及成员函数声明
*/
class LoadConfig {
private:
	static int CreateCfgFile();
	static bool ConfigFileExisting();
public:
	static int LoadConfigFile();
};