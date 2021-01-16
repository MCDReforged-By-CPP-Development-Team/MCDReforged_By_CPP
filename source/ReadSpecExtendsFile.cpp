#include "ReadSpecExtendsFile.h"

int _fastcall FilesRead(string root, vector<string>& fileVec)
{
    int Nums = 0;
    long long handle = 0;
    struct _finddata_t fileinfo;
    string temp_str;
    if ((handle = _findfirst(temp_str.assign(root).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            if ((fileinfo.attrib & _A_SUBDIR))
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    FilesRead(temp_str.assign(root).append(fileinfo.name).c_str(), fileVec);
            }
            else
            {
                try
                {
                    if (fileinfo.size == 0)
                        throw - 1;
                    else
                        fileVec.push_back(temp_str.assign(root).append("\\").append(fileinfo.name));
                }
                catch (int e)
                {
                    if (e == -1)
                        cout << "file is empty!" << endl;
                }
            }
        } while (_findnext(handle, &fileinfo) == 0);
        _findclose(handle);
    }

    Nums = (int)fileVec.size();
    if (Nums > 0)
        return Nums;
    else
        return 0;
}
