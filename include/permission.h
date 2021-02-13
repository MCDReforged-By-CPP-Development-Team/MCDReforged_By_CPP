#pragma once

#include<Windows.h>
#include<string>
#include<iostream>
#include<map>
#include<list>
#include"utils.h"
#include"logsys.h"
#include"common.h"
#include"cfgfile.h"
#include"tinyxml2-8.0.0/tinystr.h"  
#include"tinyxml2-8.0.0/tinyxml.h"

using namespace std;

#define PERMISSION_OWNER  0xffff
#define PERMISSION_ADMIN  0xfff0
#define PERMISSION_HELPER 0xff1f
#define PERMISSION_USER   0xf2ff
#define PERMISSION_GUEST  0x3fff

#define COMMOM_PF "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"\
        "<Permissions>\r\n"\
        "\t<Owner></Owner>\r\n"\
        "\t<Admin></Admin>\r\n"\
        "\t<Helper></Helper>\r\n"\
        "\t<User></User>\r\n"\
        "\t<Guest></Guest>\r\n"\
        "</Permissions>\r\n";

#define PERMISSION_FILE_NAME "permissions.xml"
class Permission
{
public:
	Permission();
	~Permission();
    //��ȡָ���û���Ȩ�� ���û�������ʱ����NULL
	DWORD stdfuncallconv GetUserPermission(LPCSTR lpUser);
    //�趨ָ���û���Ȩ�� 
    //ע�⣺��dwPermissionsΪNULLʱ���Ӹ��û�����Ȩ������ɾ�����û�
    int stdfuncallconv SetUserPermission(LPCSTR lpUser, DWORD dwPermission);

    //��ȡָ��Ȩ���������г�Ա
    int stdfuncallconv GetPermissionGroup(DWORD dwGroup, list<string> *Result);

    int stdfuncallconv SavePermission();
};

bool PermissionFileExisting();