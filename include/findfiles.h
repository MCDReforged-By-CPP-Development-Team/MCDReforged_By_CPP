#include<string>
#include<io.h>
#include<vector>

using namespace std;

int GetFiles(string fileFolderPath, string fileExtension, vector<string>& file) {
	string fileFolder = fileFolderPath + "\\*" + fileExtension;
	string fileName;
	struct _finddata_t fileInfo;
	long long findResult = _findfirst(fileFolder.c_str(), &fileInfo);
	if (findResult == -1) {
		_findclose(findResult);
		return -1;
	}
	bool flag = 0;

	do {
		fileName = fileFolderPath + "\\" + fileInfo.name;
		if (fileInfo.attrib == _A_ARCH)
		{
			file.push_back(fileName);
		}
	} while (_findnext(findResult, &fileInfo) == 0);

	_findclose(findResult);
}