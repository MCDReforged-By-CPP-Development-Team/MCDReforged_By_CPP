#include <string>
#include <vector>

#ifndef __MACH__
#include <Python.h>
#endif

#ifdef __MACH__
#include <Python/Python.h>
#endif

using namespace std;

#define PyPluginExtension ".py" //python²å¼þÀ©Õ¹Ãû
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
    void GetPyPluginPath();
    vector<PyPlugin> PyPlugins;
public:
    void LoadAllPyPlugins();
    void UnLoadAllPyPlugins();
    void ReLoadAllPyPlugins();
    void LoadSinglePlugin();
    void UnloadSinglePlugin();
    void ReloadSinglePlugin();
};