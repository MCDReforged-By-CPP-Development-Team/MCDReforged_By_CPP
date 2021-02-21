#pragma once
#include<Windows.h>
#include<vector>

//#include"cppplugin.h"
#include"pyplugin.h"
#include"globaldef.h"
#include"debugprint.h"
#include"serverparser.h"
#include"output.h"
#include"utils.h"
#include"cfgfile.h"

using namespace std;

/*
ProcessOutput首先逐句分解服务器输出内容再逐句调用相应的parser解析 获得消息类型和内容 再调用DispatchPluginMsg()将消息分发给各插件
*/

class ProcessServerOutput {
public:
	int stdfuncallconv ProcessOutput(LPSTR output, int reserved = 0);
	int stdfuncallconv CannotProcessOutput();
};