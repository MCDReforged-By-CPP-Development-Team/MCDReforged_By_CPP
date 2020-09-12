/*
SysInit.h
此头文件应当包含Initialize()和Finalize()函数的声明及SysInit.cpp所需要的include预编译语句
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