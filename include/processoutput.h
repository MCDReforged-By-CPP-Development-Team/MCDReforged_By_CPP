#pragma once
#include"cppplugin.h"
#include<Windows.h>
#include"pyplugin.h"
#include"common.h"
#include"debugprint.h"
#include"messagesys.h"

using namespace std;

/*
ProcessOutput首先逐句分解服务器输出内容再逐句调用相应的parser解析 获得消息类型和内容 再调用DispatchPluginMsg()将消息分发给各插件
*/

int stdfuncallconv ProcessOutput(LPSTR output);
int stdfuncallconv CannotProcessOutput();