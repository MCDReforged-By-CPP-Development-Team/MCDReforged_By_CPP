<<<<<<< HEAD
# Install script for directory: C:/Users/34376/source/repos/MCDReforged-By-CPP-Development-Team/MCDReforged_By_CPP/MCDReforged_By_CPP

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/34376/source/repos/MCDReforged-By-CPP-Development-Team/MCDReforged_By_CPP/MCDReforged_By_CPP/out/install/x64-Debug")
=======
# Install script for directory: C:/Users/竹子/source/repos/MCDReforged-By-CPP-Development-Team/MCDReforged_By_CPP

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/竹子/Source/Repos/MCDReforged-By-CPP-Development-Team/MCDReforged_By_CPP/out/install/x64-Debug")
>>>>>>> 9c5929d87ea17f813566f9c8e33136095e27afa0
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
<<<<<<< HEAD
file(WRITE "C:/Users/34376/source/repos/MCDReforged-By-CPP-Development-Team/MCDReforged_By_CPP/MCDReforged_By_CPP/out/build/x64-Debug/${CMAKE_INSTALL_MANIFEST}"
=======
file(WRITE "C:/Users/竹子/source/repos/MCDReforged-By-CPP-Development-Team/MCDReforged_By_CPP/out/build/x64-Debug/${CMAKE_INSTALL_MANIFEST}"
>>>>>>> 9c5929d87ea17f813566f9c8e33136095e27afa0
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
