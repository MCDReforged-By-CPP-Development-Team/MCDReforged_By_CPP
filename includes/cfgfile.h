/*
cfgfile.h
������ȡ�����ļ����༰��Ա��������
*/
class LoadConfig {
private:
	static int CreateCfgFile();
	static bool ConfigFileExisting();
public:
	static int LoadConfigFile();
};