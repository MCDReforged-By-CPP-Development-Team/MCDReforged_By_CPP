/*
SysInit.h
��ͷ�ļ�Ӧ������Initialize()��Finalize()������������SysInit.cpp����Ҫ��includeԤ�������
*/

#include"cfgfile.h"
#include"cmdsys.h"
#include"cppplugin.h"
#include"findfiles.h"
#include"globalsettings.h"
#include"logsys.h"
#include"messagesys.h"
#include"pyplugin.h"
#include"rewriteio.h"
#include"serverparser.h"
#include"common.h"

int stdfuncallconv Initialize();

int stdfuncallconv Finalize();