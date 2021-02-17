#include "utils.h"

bool have(string a, string b)
{
    if (a.find(b) != string::npos)
    {
        return true;
    }
    else
    {
        return false;
    }
}

vector<string> split(const string& str, const string& pattern)
{
    //const char* convert to char*
    char* strc = new char[strlen(str.c_str()) + 1];
    strcpy(strc, str.c_str());
    vector<string> resultVec;
    char* tmpStr = strtok(strc, pattern.c_str());
    while (tmpStr != NULL)
    {
        resultVec.push_back(string(tmpStr));
        tmpStr = strtok(NULL, pattern.c_str());
    }

    delete[] strc;

    return resultVec;
}

list<string> splittolist(const string& str, const string& pattern)
{
    //const char* convert to char*
    char* strc = new char[strlen(str.c_str()) + 1];
    strcpy(strc, str.c_str());
    list<string> resultList;
    char* tmpStr = strtok(strc, pattern.c_str());
    while (tmpStr != NULL)
    {
        resultList.push_back(string(tmpStr));
        tmpStr = strtok(NULL, pattern.c_str());
    }

    delete[] strc;

    return resultList;
}

string makestring(list<string> list_ , string spiliter)
{
    string result;
    for (auto iter = list_.begin();iter != list_.end() ;iter++)
    {
        result.append(iter->c_str());
        if (iter == list_.end())
        {
            //在结尾不加分隔符
        }
        else
        {
            result.append(spiliter);
        }
    }
    return string();
}

string makestring(vector<string> list_, string spiliter)
{
    string result;
    for (auto iter = list_.begin(); iter != list_.end(); iter++)
    {
        result.append(iter->c_str());
        if (iter == list_.end())
        {
            //在结尾不加分隔符
        }
        else
        {
            result.append(spiliter);
        }
    }
    return string();
}


//寻找文件夹是否存在 strpath:目录
//返回true即为文件夹存在 返回false为文件夹不存在或者为文件
bool CheckFolderExist(const string& strPath) {
    HANDLE hTest;
    string folder;
    folder.append(".\\").append(strPath);
    WIN32_FIND_DATA wfdFind;
    hTest = FindFirstFile(folder.c_str(), &wfdFind);
    if ((hTest == INVALID_HANDLE_VALUE) && wfdFind.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
    {
        FindClose(hTest);
        return true;
    }
    return false;
}

vector<string> stdfuncallconv ListFiles(string path)
{
    CheckFolderExist(path);
    HANDLE hFind;
    vector<string> result;
    string path_ = path + "\\*";
    WIN32_FIND_DATA wfdFind;
    hFind = FindFirstFile(path_.c_str(), &wfdFind);
    DWORD dwError = 0;
    if (hFind == INVALID_HANDLE_VALUE){}
    else
    {
        string tmp;
        do
        {
            if (wfdFind.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {

            }
            else
            {
                tmp = wfdFind.cFileName;
                result.push_back(tmp);
            }
        } while (FindNextFile(hFind, &wfdFind) != 0);
        dwError = GetLastError();
        if (dwError != ERROR_NO_MORE_FILES)
        {
            return result;
        }
        
    }
    FindClose(hFind);
    return result;
}

vector<string>stdfuncallconv ListFiles(string path, string ext)
{
    CheckFolderExist(path);
    HANDLE hFind;
    vector<string> result;
    string path_ = path + "\\*";
    WIN32_FIND_DATA wfdFind;
    hFind = FindFirstFile(path_.c_str(), &wfdFind);
    DWORD dwError = 0;
    if (hFind == INVALID_HANDLE_VALUE) {}
    else
    {
        string tmp;
        do
        {
            if (wfdFind.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {

            }
            else
            {
                tmp = wfdFind.cFileName;
                vector<string> filenames = split(tmp, ".");
                if (filenames[filenames.size()+1] == ext)
                {
                    result.push_back(tmp);
                }

            }
        } while (FindNextFile(hFind, &wfdFind) != 0);
        dwError = GetLastError();
        if (dwError != ERROR_NO_MORE_FILES)
        {
            return result;
        }

    }
    FindClose(hFind);
    return result;
}



template<class T1, class T2> vector<T1> del(vector<T1> a, T2 to_be_removed_obj)
{
    for (vector<int>::iterator iter = a.begin(); iter != a.end(); iter++) {
        if (*iter == to_be_removed_obj) {
            a.erase(iter);
            break;
        }
    }
    return a;
}

string stdfuncallconv CreateGuid(GUID* pguid)
{
    char buffer[GUID_LEN] = { 0 };
    GUID guid;
    if (CoCreateGuid(&guid))
    {
        return "";
    }
    _snprintf(buffer, sizeof(buffer), "%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
        guid.Data1, guid.Data2, guid.Data3,
        guid.Data4[0], guid.Data4[1], guid.Data4[2],
        guid.Data4[3], guid.Data4[4], guid.Data4[5],
        guid.Data4[6], guid.Data4[7]);

    *pguid = guid;
    return string(buffer);
}

int stdfuncallconv CompareVersion(string Ver1, string Ver2) {
    Ver1.erase(Ver1.find('.'));
    Ver1.erase(Ver1.find('.'));
    Ver2.erase(Ver2.find('.'));
    Ver2.erase(Ver2.find('.'));
    
    strstream sstr1, sstr2;
    sstr1 << Ver1;
    sstr2 << Ver2;
    int iver1, iver2;
    sstr1 >> iver1;
    sstr2 >> iver2;

    if (iver1 > iver2) return 1;
    else if (iver1 < iver2) return -1;
    else return 0;
}