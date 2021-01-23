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


int stdfuncallconv CppPluginCore::LoadPlugin() {	//用于加载所有C/C++插件的函数
	vector<string> PluginFileNames;
	char pathBuf[MAX_PATH];
	GetCurrentDirectoryA(sizeof(pathBuf), pathBuf);
	string tempStr = pathBuf;
	string pluginFolderPath = tempStr + "\\plugins";	//存放插件文件夹路径
	FilesRead(pluginFolderPath, PluginFileNames);	//遍历插件文件夹下所有.dll的插件文件
	if (PluginFileNames.size() <= 0) {
		return 0;	//后面再来做错误逻辑吧=-=
	}
	for (int i = 0; i < PluginFileNames.size(); i ++) {
		HMODULE HPlugin = LoadLibrary(PluginFileNames[i].c_str());	//加载插件
		if (HPlugin == NULL) {
			continue;	//后面再来做错误逻辑吧=-=
		}
		pFuncOnCheck FuncCheck = (pFuncOnCheck)GetProcAddress(HPlugin, "OnCheck");	//假定插件实现了OnCheck函数
		if (FuncCheck == NULL) {
			continue;	//后面再来做错误逻辑吧=-=
		}
		int iRet = FuncCheck(i);
		if (iRet != i++) {	//如果OnCheck的返回值不等于传入参数+1,插件校验失败
			continue;	//后面再来做错误逻辑吧=-=
		}
		pFuncRegInfo FuncReg = (pFuncRegInfo)GetProcAddress(HPlugin, "RegInfo");	//假定插件实现了RegInfo函数
		if (FuncReg == NULL) {
			continue;	//后面再来做错误逻辑吧=-=
		}
		_CppPluginRegInfo RegInfo = FuncReg();
		RegPlugin(RegInfo);
		pFuncOnLoad FuncLoad = (pFuncOnLoad)GetProcAddress(HPlugin, "OnLoad");	//假定插件实现了OnLoad函数
		if (FuncLoad == NULL) {
			continue;	//后面再来做错误逻辑吧=-=
		}
	    iRet = FuncLoad();
		if (iRet == -1) {
			continue;	//后面再来做错误逻辑吧=-=
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
