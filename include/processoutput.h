#pragma once
#include<Windows.h>
#include"cppplugin.h"
#include"pyplugin.h"
#include"common.h"
#include"debugprint.h"
#include"messagesys.h"
#include"serverparser.h"

using namespace std;

/*
ProcessOutput�������ֽ�����������������������Ӧ��parser���� �����Ϣ���ͺ����� �ٵ���DispatchPluginMsg()����Ϣ�ַ��������
*/

class ProcessServerOutput {
public:
	int stdfuncallconv ProcessOutput(LPSTR output, int reserved);
	int stdfuncallconv CannotProcessOutput();
};