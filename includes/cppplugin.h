#include<string>
#include<vector>

#include<Windows.h>

using namespace std;

struct _CppPluginRegInfo;	//ǰ������

#define MAX_CMD_NUM 255	//����ע��ָ����Ϊ255��
#define CppPluginExtension ".dll"	//�����չ��

typedef int(*pFuncOnLoad)();	//��������OnLoad����ԭ��
typedef _CppPluginRegInfo(*pFuncRegInfo)();	//��������RegInfo����ԭ��
typedef int(*pFuncOnCheck)(int a);	//��������OnCheck����ԭ��

struct _CppPluginRegInfo {
	int PluginID;	//�˲����Ψһ��ʶ��
	string PluginRegName;	//�˲����ע������
	string PluginRegPath;	//�˲�����ļ�·��
	vector<string> PluginRegCmd;	//�˲��ע���ָ��
	HMODULE PluginHandle;	//�˲���ľ��

	void operator=(_CppPluginRegInfo Source) {
		this->PluginID = Source.PluginID;
		this->PluginRegName = Source.PluginRegName;
		this->PluginRegPath = Source.PluginRegPath;
		for (int i = 0; i < Source.PluginRegCmd.size(); i++) this->PluginRegCmd[i] = Source.PluginRegCmd[i];
		this->PluginHandle = Source.PluginHandle;
	}
};

struct CppPluginCore {	//���ýṹ���װ���������û�����,����ʵ�ַ���cppplugin.cpp���� awa
    private:
	    int RegPlugin(_CppPluginRegInfo info);
	    vector<_CppPluginRegInfo> CppPluginRegInfo;	//����C/C++��������ṹ���vector
    public:
	    int LoadPlugin();
	    int OnCmd();
};