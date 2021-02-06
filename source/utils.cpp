#include "utils.h"


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

//Ѱ���ļ����Ƿ���� strpath:Ŀ¼
//����true��Ϊ�ļ��д��� ����falseΪ�ļ��в����ڻ���Ϊ�ļ�
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

