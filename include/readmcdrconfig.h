#pragma once

#include<vector>

#include"output.h"
#include"yamlcpp/yaml-cpp/yaml.h"
#include"globaldef.h"
#include"cfgfile.h"
#include"permission.h"


using namespace std;

int stdfuncallconv ReadMCDRConfig_0();
int stdfuncallconv ReadMCDRConfig_1();

int stdfuncallconv ReadMCDRPermission();

/*
mcdr premission.yml 0.x
# This is the permission config and storage file of MCDReforged
# It is used to storage permission level stuffs of MCDR
# Available levels (top to down):
# - owner
# - admin
# - helper
# - user
# - guest


default_level: user

owner:
- Fallen_Breath
admin:
helper:
user:
guest:

*/