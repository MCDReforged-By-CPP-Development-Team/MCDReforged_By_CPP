#pragma once
#include"cppplugin.h"
#include<Windows.h>
#include"pyplugin.h"
#include"common.h"
#include"debugprint.h"
#include"messagesys.h"

using namespace std;

/*
ProcessOutput�������ֽ�����������������������Ӧ��parser���� �����Ϣ���ͺ����� �ٵ���DispatchPluginMsg()����Ϣ�ַ��������
*/

int stdfuncallconv ProcessOutput(LPSTR output);
int stdfuncallconv CannotProcessOutput();