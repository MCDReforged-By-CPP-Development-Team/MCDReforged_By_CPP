#####################################################
# 创建者 ixiaohei
# 最后更改日期/编译成功日期 2020/08/17 12:27:11
# 如果没有新增/减少源代码文件，请尽量不要更改此CMakeLists.txt
#####################################################

cmake_minimum_required(VERSION 3.16)
project(MCDReforged_By_CPP)

set(CMAKE_HOST_SYSTEM_VERSION "10.0.17763.0")

#set(CMAKE_CXX_STANDARD 20)
#C++ 17 以上版本都会报错 所以把他注释掉


aux_source_directory(./source DIR_SRCS)
aux_source_directory(./include DIR_INC)
aux_source_directory(./tinyxml2-8.0.0 DIR_TNY)

IF(WIN32)

    #message(CMAKE_SYSTEM_VERSION)
    MESSAGE(STATUS Cmaking on windowsx86_64)
    set(PYINCLUDE "d:/Program Files/Python38/include")
    set(PYLIB "d:/Program Files/Python38/libs")

    link_directories(${PYLIB})
    #link_libraries(此编译选项为玄学选项，请填写自己计算机的python lib 路径. ps: 系统环境变量不能用，我试过了 请不要把这个选项改动后推到github)

    include_directories(${PYINCLUDE})
    include_directories(.)
    include_directories(include)
    include_directories(tinyxml2-8.0.0)

    add_executable(MCDReforged_By_CPP
            ${PYINCLUDE}/Python.h
            ${DIR_SRCS}
            ${DIR_INC}
            ${DIR_TNY} )
            #温馨提示:这里会自动搜寻source,include和tinyxml2-8.0.0,因此除非特殊情况,不要手动更改或使用vs的自动更改修改此处
ELSEIF(APPLE)
    MESSAGE(STATUS Cmaking on APPLE MacOS)
    include_directories(.)
    include_directories(include)
    include_directories(tinyxml2-8.0.0)

    add_executable(MCDReforged_By_CPP
            ${DIR_SRCS}
            ${DIR_INC}
            ${DIR_TNY})
            #同上
ENDIF()
