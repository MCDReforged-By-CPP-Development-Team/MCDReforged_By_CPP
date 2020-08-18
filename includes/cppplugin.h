#include<string>
#include<vector>

#include<Windows.h>

using namespace std;

struct _CppPluginRegInfo;	//前置声明

#define MAX_CMD_NUM 255	//最大可注册指令数为255个
#define CppPluginExtension ".dll"	//插件扩展名

typedef int(*pFuncOnLoad)();	//定义插件中OnLoad函数原型
typedef _CppPluginRegInfo(*pFuncRegInfo)();	//定义插件中RegInfo函数原型
typedef int(*pFuncOnCheck)(int a);	//定义插件中OnCheck函数原型

struct _CppPluginRegInfo {
	int PluginID;	//此插件的唯一标识符
	string PluginRegName;	//此插件的注册名称
	string PluginRegPath;	//此插件的文件路径
	vector<string> PluginRegCmd;	//此插件注册的指令
	HMODULE PluginHandle;	//此插件的句柄

	void operator=(_CppPluginRegInfo Source) {
		this->PluginID = Source.PluginID;
		this->PluginRegName = Source.PluginRegName;
		this->PluginRegPath = Source.PluginRegPath;
		for (int i = 0; i < Source.PluginRegCmd.size(); i++) this->PluginRegCmd[i] = Source.PluginRegCmd[i];
		this->PluginHandle = Source.PluginHandle;
	}
};

struct CppPluginCore {	//采用结构体封装函数避免用户误用,函数实现放在cppplugin.cpp里面 awa
    private:
	    int RegPlugin(_CppPluginRegInfo info);
	    vector<_CppPluginRegInfo> CppPluginRegInfo;	//保存C/C++插件描述结构体的vector
    public:
	    int LoadPlugin();
	    int OnCmd();
};