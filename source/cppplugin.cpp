//c++ & c headers begin...
#include <string>
#include <vector>
//end; SB Windows Header begin...
#include <Windows.h>
//end; Header in Project...
#include "cppplugin.h"
#include "findfiles.h"
//end;

using namespace std;

int stdfuncallconv CppPluginCore::LoadPlugin() {	//���ڼ�������C/C++����ĺ���
	vector<string> PluginFileNames;
	char pathBuf[MAX_PATH];
	GetCurrentDirectoryA(sizeof(pathBuf), pathBuf);
	string tempStr = pathBuf;
	string pluginFolderPath = tempStr + "\\plugins";	//��Ų���ļ���·��
	GetFiles(pluginFolderPath, CppPluginExtension, PluginFileNames);	//��������ļ���������.dll�Ĳ���ļ�
	if (PluginFileNames.size() <= 0) {
		return 0;	//���������������߼���=-=
	}
	for (int i = 0; i < PluginFileNames.size(); i ++) {
		HMODULE HPlugin = LoadLibraryA(PluginFileNames[i].c_str());	//���ز��
		if (HPlugin == NULL) {
			continue;	//���������������߼���=-=
		}
		pFuncOnCheck FuncCheck = (pFuncOnCheck)GetProcAddress(HPlugin, "OnCheck");	//�ٶ����ʵ����OnCheck����
		if (FuncCheck == NULL) {
			continue;	//���������������߼���=-=
		}
		int iRet = FuncCheck(i);
		if (iRet != i++) {	//���OnCheck�ķ���ֵ�����ڴ������+1,���У��ʧ��
			continue;	//���������������߼���=-=
		}
		pFuncRegInfo FuncReg = (pFuncRegInfo)GetProcAddress(HPlugin, "RegInfo");	//�ٶ����ʵ����RegInfo����
		if (FuncReg == NULL) {
			continue;	//���������������߼���=-=
		}
		_CppPluginRegInfo RegInfo = FuncReg();
		RegPlugin(RegInfo);
		pFuncOnLoad FuncLoad = (pFuncOnLoad)GetProcAddress(HPlugin, "OnLoad");	//�ٶ����ʵ����OnLoad����
		if (FuncLoad == NULL) {
			continue;	//���������������߼���=-=
		}
	    iRet = FuncLoad();
		if (iRet == -1) {
			continue;	//���������������߼���=-=
		}
	}
	return 0;
}

int stdfuncallconv CppPluginCore::RegPlugin(_CppPluginRegInfo info) {
	CppPluginRegInfo.push_back(info);
	return 0;
}
