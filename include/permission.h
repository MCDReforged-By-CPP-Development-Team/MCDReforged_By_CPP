#pragma once

#include<Windows.h>

#include"common.h"

#include"tinyxml2-8.0.0/tinystr.h"  
#include"tinyxml2-8.0.0/tinyxml.h"

using namespace std;

#define PERMISSION_LEVEL_OWNER 4
#define PERMISSION_LEVEL_ADMIN 3
#define PERMISSION_LEVEL_HELPER 2
#define PERMISSION_LEVEL_USER 1
#define PERMISSION_LEVEL_GUEST 0

#define PERMISSION_FILE_NAME

int stdfuncallconv ReadPermFile();
