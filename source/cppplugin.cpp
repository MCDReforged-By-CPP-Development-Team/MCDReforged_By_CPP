#include "cppplugin.h"
#include <corecrt_io.h>


int stdfuncallconv CppPluginCore::FilesRead(string root, vector<string>& fileVec)
{
	int Nums = 0;
	long long handle = 0;
	struct _finddata_t fileinfo;
	string temp_str;
	if ((handle = _findfirst(temp_str.assign(root).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					FilesRead(temp_str.assign(root).append(fileinfo.name).c_str(), fileVec);
			}
			else
			{
				try
				{
					if (fileinfo.size == 0)
						throw - 1;
					else
						fileVec.push_back(temp_str.assign(root).append("\\").append(fileinfo.name));
				}
				catch (int e)
				{
					if (e == -1)
						cout << "file is empty!" << endl;
				}
			}
		} while (_findnext(handle, &fileinfo) == 0);
		_findclose(handle);
	}

	Nums = (int)fileVec.size();
	if (Nums > 0)
		return Nums;
	else
		return 0;
}


int stdfuncallconv CppPluginCore::LoadPlugin() {	//���ڼ�������C/C++����ĺ���
	vector<string> PluginFileNames;
	char pathBuf[MAX_PATH];
	GetCurrentDirectoryA(sizeof(pathBuf), pathBuf);
	string tempStr = pathBuf;
	string pluginFolderPath = tempStr + "\\plugins";	//��Ų���ļ���·��
	FilesRead(pluginFolderPath, PluginFileNames);	//��������ļ���������.dll�Ĳ���ļ�
	if (PluginFileNames.size() <= 0) {
		return 0;	//���������������߼���=-=
	}
	for (int i = 0; i < PluginFileNames.size(); i ++) {
		HMODULE HPlugin = LoadLibrary(PluginFileNames[i].c_str());	//���ز��
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

int stdfuncallconv CppPluginCore::OnCmd()
{
	return 0;
}

int stdfuncallconv CppPluginCore::RegPlugin(_CppPluginRegInfo info) {
	CppPluginRegInfo.push_back(info);
	return 0;
}
