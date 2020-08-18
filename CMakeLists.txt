#####################################################
# 创建者 ixiaohei
# 最后更改日期/编译成功日期 2020/08/17 12:27:11
# 如果没有新增/减少源代码文件，请尽量不要更改此CMakeLists.txt
#####################################################

cmake_minimum_required(VERSION 3.16)
project(MCDReforged_By_CPP)

set(CMAKE_CXX_STANDARD 20)

IF(WIN32)
    MESSAGE(STATUS Cmaking on windowsx86_64)
    set(PYINCLUDE C:/Users/apple/AppData/Local/Programs/Python/Python38/include)
    set(PYLIB C:/Users/apple/AppData/Local/Programs/Python/Python38/libs)

    link_directories(${PYLIB})
    #link_libraries(此编译选项为玄学选项，请填写自己计算机的python lib 路径. ps: 系统环境变量不能用，我试过了 请不要把这个选项改动后推到github)

    include_directories(${PYINCLUDE})
    include_directories(.)
    include_directories(includes)
    include_directories(include)

    add_executable(MCDReforged_By_CPP
            ${PYINCLUDE}/Python.h
            includes/cppplugin.h
            includes/findfiles.h
            includes/pyplugin.h
            includes/rewriteio.h
            includes/SysInit.h
            source/cppplugin.cpp
            source/pyplugin.cpp
            source/SysInit.cpp
            MCDRCPP.cpp
            MCDRCPP.h)
ELSEIF(APPLE)
    MESSAGE(STATUS Cmaking on APPLE MacOS)
    include_directories(.)
    include_directories(includes)
    include_directories(include)

    add_executable(MCDReforged_By_CPP
            includes/cppplugin.h
            includes/findfiles.h
            includes/pyplugin.h
            includes/rewriteio.h
            includes/SysInit.h
            source/cppplugin.cpp
            source/pyplugin.cpp
            source/SysInit.cpp
            MCDRCPP.cpp
            MCDRCPP.h)
ENDIF()