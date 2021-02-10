#include"permission.h"

map<DWORD, list<string>> permissions;

bool GetNodePointerByName(TiXmlElement* pRootEle, const char* strNodeName, TiXmlElement*& Node)    //À´×ÔCSDN£ºhttps://blog.csdn.net/masikkk/article/details/14191933?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.add_param_isCf&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.add_param_isCf
{
    if (0 == strcmp(strNodeName, pRootEle->Value()))
    {
        Node = pRootEle;
        return true;
    }

    TiXmlElement* pEle = pRootEle;
    for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement())
    {
        if (0 != strcmp(pEle->Value(), strNodeName))
        {
            GetNodePointerByName(pEle, strNodeName, Node);
        }
        else
        {
            Node = pEle;
            return true;
        }
    }

    return false;
}

int ReadPermissionFile()
{
    TiXmlDocument doc(PERMISSION_FILE_NAME);

}


int CreatePermissionFile()
{
    char strCfgPath[MAX_PATH] = {};
    char strCfgFile[] = COMMOM_PF;
    DWORD dwWriteBytes;

    HANDLE hFile = ::CreateFile(
        PERMISSION_FILE_NAME,
        GENERIC_WRITE | GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        0);

    if (hFile == INVALID_HANDLE_VALUE) return false;
    WriteFile(hFile, strCfgFile, sizeof(strCfgFile), &dwWriteBytes, NULL);
    CloseHandle(hFile);
    return 0;
}


Permission::Permission()
{
    if (!PermissionFileExisting())
    {
        CreatePermissionFile();
    }
    ReadPermissionFile();

}

bool PermissionFileExisting() {
    char strCfgPath[MAX_PATH];
    GetModuleFileName(NULL, strCfgPath, MAX_PATH);
    (strrchr(strCfgPath, '\\'))[1] = 0;
    strcat_s(strCfgPath, PERMISSION_FILE_NAME);

    HANDLE hFile = ::CreateFile(
        strCfgPath,
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        0);
    if (hFile == INVALID_HANDLE_VALUE) return false;
    CloseHandle(hFile);
    return true;
}

Permission::~Permission()
{
    //permissions.clear();
}

DWORD stdfuncallconv Permission::GetUserPermission(LPCSTR lpUser)
{
	DWORD _dwPermission;
    if (permissions.empty())
    {
        return false;
    }
    for (auto it = permissions.begin();it != permissions.end();it++)
    {
        auto group = it->first;
        for (auto itt = it->second.begin() ;itt != it->second.end() ; itt++)
        {
            if (itt->c_str() == lpUser)
            {
                return group;
            }
        }
    }
	return false;
}

int stdfuncallconv Permission::GetPermissionGroup(DWORD dwGroup, list<string>* Result)
{
    list<string> _result;
    if (permissions.empty())
    {
        return false;
    }
    switch (dwGroup)
    {
    case PERMISSION_ADMIN:
        _result = permissions.at(PERMISSION_ADMIN);
        break;
    case PERMISSION_USER:
        _result = permissions.at(PERMISSION_USER);
        break;
    case PERMISSION_GUEST:
        _result = permissions.at(PERMISSION_GUEST);
        break;
    case PERMISSION_OWNER:
        _result = permissions.at(PERMISSION_OWNER);
        break;
    case PERMISSION_HELPER:
        _result = permissions.at(PERMISSION_HELPER);
        break;
    default:
        break;
    }
    _result = *Result;
    return 0;
}


