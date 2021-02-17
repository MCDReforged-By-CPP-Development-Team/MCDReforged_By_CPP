#pragma once

#include <string>
#include <vector>

#include "globaldef.h"

#ifndef __MACH__
#include <Python.h>
#endif

#ifdef __MACH__
#include <Python/Python.h>
#endif

using namespace std;

#define PyPluginExtension ".py" //python插件扩展名
#define PyPluginDir "pyplugins"

struct PyPlugin {
    string PluginName = "none";
    string PluginFileName = "none";
    string PluginPath = "none";
    PyObject on_load;
    PyObject on_unload;
    PyObject on_info;
    PyObject on_user_info;
    PyObject on_player_joined;
    PyObject on_player_left;
    PyObject on_death_message;
    PyObject on_player_made_advancement;
    PyObject on_server_startup;
    PyObject on_server_stop;
    PyObject on_mcdr_stop;
};

struct PyPluginCore {
private:
    void stdfuncallconv GetPyPluginPath();
    vector<PyPlugin> PyPlugins;
public:
    void stdfuncallconv LoadAllPyPlugins();
    void stdfuncallconv UnLoadAllPyPlugins();
    void stdfuncallconv ReLoadAllPyPlugins();
    void stdfuncallconv LoadSinglePlugin();
    void stdfuncallconv UnloadSinglePlugin();
    void stdfuncallconv ReloadSinglePlugin();
};
