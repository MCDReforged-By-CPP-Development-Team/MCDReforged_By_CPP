#include"permission.h"

map<DWORD, list<string>> permissions;

bool GetNodePointerByName(TiXmlElement* pRootEle, const char* strNodeName, TiXmlElement*& Node)    //来自CSDN：https://blog.csdn.net/masikkk/article/details/14191933?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.add_param_isCf&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.add_param_isCf
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
    int iret = false;
    TiXmlDocument Doc(PERMISSION_FILE_NAME);
    iret = Doc.LoadFile(TIXML_ENCODING_UTF8);
    string tinyxmlerror = ("ErrorID:" + Doc.ErrorId());
    tinyxmlerror += "ErrorDesc:";
    tinyxmlerror += Doc.ErrorDesc();
    if (!iret) {
        dp("Doc.LoadFile() failed.");
        dp(tinyxmlerror);
        return -1;
    }
    dp("Load Config File Successful.");
    TiXmlElement* pRootEle = Doc.RootElement();
    if (pRootEle == NULL) {
        dp("Doc.RootElement(); failed.");
        return -1;
    }
    dp("Get XML Root Element Successful.");

    TiXmlElement* pElem = NULL;
    string gttemp;

    GetNodePointerByName(pRootEle, "Owner", pElem);
    permissions.clear();
    rettest
    gttemp = gt;
    auto list_ = splittolist(gt, ";");
    permissions[PERMISSION_OWNER] = list_;
    dp(gt);
    dp("Read Permission Successful.#PERMISSION_OWNER");

    GetNodePointerByName(pRootEle, "Admin", pElem);
    rettest
    gttemp = gt;
    list_ = splittolist(gt, ";");
    permissions[PERMISSION_ADMIN] = list_;
    dp(gt);
    dp("Read Permission Successful.##PERMISSION_ADMIN");

    GetNodePointerByName(pRootEle, "Helper", pElem);
    rettest
    gttemp = gt;
    list_ = splittolist(gt, ";");
    permissions[PERMISSION_HELPER] = list_;
    dp(gt);
    dp("Read Permission Successful.###PERMISSION_HELPER");

    GetNodePointerByName(pRootEle, "User", pElem);
    rettest
    gttemp = gt;
    list_ = splittolist(gt, ";");
    permissions[PERMISSION_USER] = list_;
    dp(gt);
    dp("Read Permission Successful.####PERMISSION_USER");

    GetNodePointerByName(pRootEle, "Guest", pElem);
    rettest
    gttemp = gt;
    list_ = splittolist(gt, ";");
    permissions[PERMISSION_GUEST] = list_;
    dp(gt);
    dp("Read Permission Successful.#####PERMISSION_GUEST");
    return 114514;
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
    SavePermission();
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
                SavePermission();
                return group;
            }
        }
    }
	return false;
}

int Permission::SetUserPermission(LPCSTR lpUser, DWORD dwPermission)
{
    int iret = NULL;
    if (lpUser == NULL)
    {
        return iret;
    }
    if (dwPermission == NULL)
    {
        //从该用户所在权限组中删除该用户
        DWORD dwUserPermission = GetUserPermission(lpUser);
        auto UserList = permissions.at(dwUserPermission);
        string usertmp = lpUser;
        iret = UserList.remove(usertmp);
        permissions[dwPermission] = UserList;
        SavePermission();
        return iret;
    }
    else
    {
        //先从该用户所在权限组中删除该用户
        DWORD dwUserPermission = GetUserPermission(lpUser);
        auto UserList = permissions.at(dwUserPermission);
        string UserName = lpUser;
        iret += UserList.remove(UserName);
        permissions[dwUserPermission] = UserList;
        //然后再在给定组内添加该用户
        auto tmpList = permissions.at(dwPermission);
        iret += tmpList.push_back(UserName);
        permissions[dwPermission] = tmpList;
        SavePermission();
        return iret;
    }
    
    
    return 0;
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
    SavePermission();
    return 0;
}


