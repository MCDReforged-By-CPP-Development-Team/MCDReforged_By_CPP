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
	//return PERMISSION_USER; //不在permission文件中的用户的默认权限
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
        UserList.remove(usertmp);
        permissions[dwPermission] = UserList;
        SavePermission();
        return iret;
    }
    else
    {
        if (GetUserPermission(lpUser) != false)//用户是否存在
        {
            //先从该用户所在权限组中删除该用户
            DWORD dwUserPermission = GetUserPermission(lpUser);
            auto UserList = permissions.at(dwUserPermission);
            string UserName = lpUser;
            UserList.remove(UserName);
            permissions[dwUserPermission] = UserList;
            //然后再在给定组内添加该用户
            auto tmpList = permissions.at(dwPermission);
            tmpList.push_back(UserName);
            permissions[dwPermission] = tmpList;
            SavePermission();
            return iret;
        }
        else
        {
            return iret;
        }
    }
    
    
    return iret;
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

int Permission::SavePermission()
{
    int iret = false;
    CreatePermissionFile();
    TiXmlDocument* pDoc = new TiXmlDocument;
    if (NULL == pDoc)
    {
        return false;
    }
    TiXmlDeclaration* pDeclaration = new TiXmlDeclaration("1.0", "UTF-8", " ");
    if (NULL == pDeclaration)
    {
        return false;
    }
    dp("create doc and decl successfully.");
    pDoc->LinkEndChild(pDeclaration);
    TiXmlElement* pRootEle = new TiXmlElement("Permissions");
    if (NULL == pRootEle)
    {
        return false;
    }
    pDoc->LinkEndChild(pRootEle);
    TiXmlElement* pOwnerEle = new TiXmlElement("Owner");
    if (NULL == pOwnerEle)
    {
        return false;
    }
    TiXmlText* pOwnerText = new TiXmlText(makestring(permissions.at(PERMISSION_OWNER), ";").c_str());
    pOwnerEle->LinkEndChild(pOwnerText);
    pRootEle->LinkEndChild(pOwnerEle);

    TiXmlElement* pAdminEle = new TiXmlElement("Admin");
    if (NULL == pAdminEle)
    {
        return false;
    }
    TiXmlText* pAdminText = new TiXmlText(makestring(permissions.at(PERMISSION_ADMIN), ";").c_str());
    pAdminEle->LinkEndChild(pOwnerText);
    pRootEle->LinkEndChild(pAdminEle);

    TiXmlElement* pHelperEle = new TiXmlElement("Helper");
    if (NULL == pHelperEle)
    {
        return false;
    }
    TiXmlText* pHelperText = new TiXmlText(makestring(permissions.at(PERMISSION_HELPER), ";").c_str());
    pHelperEle->LinkEndChild(pHelperText);
    pRootEle->LinkEndChild(pHelperEle);

    TiXmlElement* pGuestEle = new TiXmlElement("Guest");
    if (NULL == pGuestEle)
    {
        return false;
    }
    TiXmlText* pGuestText = new TiXmlText(makestring(permissions.at(PERMISSION_GUEST), ";").c_str());
    pGuestEle->LinkEndChild(pGuestText);
    pRootEle->LinkEndChild(pGuestEle);

    TiXmlElement* pUserEle = new TiXmlElement("User");
    if (NULL == pUserEle)
    {
        return false;
    }
    TiXmlText* pUserText = new TiXmlText(makestring(permissions.at(PERMISSION_USER), ";").c_str());
    pUserEle->LinkEndChild(pUserText);
    pRootEle->LinkEndChild(pUserEle);

    iret = pDoc->SaveFile();
    return iret;

}


