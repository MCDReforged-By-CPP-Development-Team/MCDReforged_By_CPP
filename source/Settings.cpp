#include"Settings.h"

int stdfuncallconv GetInt(int set)
{
    switch (set)
    {
    case parsertype:
        return _set_.iParserType;
        break;
    case lang:
        return _set_.iLangType;
        break;
    default:
        return -1;
        break;
    }
    return 0;
}

bool stdfuncallconv GetBool(int set)
{
    switch (set)
    {
    case loadcppplugins:
        return _set_.bLoadCppPlugins;
        break;
    case loadpyplugins:
        return _set_.bLoadPyPlugins;
        break;
    case execinitscr:
        return _set_.bExecInitScript;
        break;
    case exectimerscr:
        return _set_.bExecTimerScript;
        break;
    case readcpppluginscfg:
        return _set_.bReadCppPluginsCfg;
        break;
    case readpypluginscfg:
        return _set_.bReadPyPluginsCfg;
        break;
    case enablemccmdqueue:
        return _set_.bEnableMinecraftCommandQueue;
        break;
    default:
        break;
    }
    return false;
}

string stdfuncallconv GetString(int set)
{
    switch (set)
    {
    case javapath:
        return _set_.strJavaPath;
        break;
    case serverdir:
        return _set_.strServerWorkingDir;
        break;
    case servername:
        return _set_.strMinecraftServerStartupCommandLine;
        break;
    case cpppluginpath:
        return _set_.strCppPluginPath;
        break;
    case pypluginpath:
        return _set_.strPyPluginPath;
        break;
    case scrpath:
        return _set_.strScriptPath;
        break;
    case insprefix:
        return _set_.strInstructionPrefix;
        break;
    case logpath:
        return _set_.strLogFilePath;
        break;
    default:
        break;
    }
    return "";
}

int stdfuncallconv SetInt(int set, int value)
{
    switch (set)
    {
    case parsertype:
        _set_.iParserType = value;
        break;
    case lang:
        _set_.iLangType = value;
        break;
    default:
        return -1;
        break;
    }
    return 0;
}

bool stdfuncallconv SetBool(int set, bool value)
{
    switch (set)
    {
    case loadcppplugins:
        _set_.bLoadCppPlugins = value;
        break;
    case loadpyplugins:
        _set_.bLoadPyPlugins = value;
        break;
    case execinitscr:
        _set_.bExecInitScript = value;
        break;
    case exectimerscr:
        _set_.bExecTimerScript = value;
        break;
    case readcpppluginscfg:
        _set_.bReadCppPluginsCfg = value;
        break;
    case readpypluginscfg:
        _set_.bReadPyPluginsCfg = value;
        break;
    case enablemccmdqueue:
        _set_.bEnableMinecraftCommandQueue = value;
        break;
    default:
        break;
    }
    return false;
}

string stdfuncallconv SetString(int set, string value)
{
    switch (set)
    {
    case javapath:
        _set_.strJavaPath = value;
        break;
    case serverdir:
        _set_.strServerWorkingDir = value;
        break;
    case servername:
        _set_.strMinecraftServerStartupCommandLine = value;
        break;
    case cpppluginpath:
        _set_.strCppPluginPath = value;
        break;
    case pypluginpath:
        _set_.strPyPluginPath = value;
        break;
    case scrpath:
        _set_.strScriptPath;
        break;
    case insprefix:
        _set_.strInstructionPrefix = value;
        break;
    case logpath:
        _set_.strLogFilePath = value;
        break;
    default:
        break;
    }
    return "";
}