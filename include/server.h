#pragma once

#include<Windows.h>

#include"redirectstdio.h"
#include"globaldef.h"
//真tm是个巨坑 插件开发核心代码
class ServerInterface {
public:
	int stdfuncallconv start();
	int stdfuncallconv stop();
	int stdfuncallconv restart();
	int stdfuncallconv wait_for_start();
	int stdfuncallconv stop_exit();
	int stdfuncallconv exit();

	bool stdfuncallconv is_server_running();
	bool stdfuncallconv is_server_startup();
	bool stdfuncallconv is_rcon_running();

	DWORD stdfuncallconv get_server_pid();

	int stdfuncallconv execute();
	int stdfuncallconv tell();
	int stdfuncallconv say();
	int stdfuncallconv boardcast();
	int stdfuncallconv reply();

	int stdfuncallconv load_plugin();
	int stdfuncallconv unload_plugin();
	int stdfuncallconv reload_plugin();
	int stdfuncallconv enable_plugin();
	int stdfuncallconv disable_plugin();
	int stdfuncallconv refresh_all_plugins();
	int stdfuncallconv refresh_changes_plugins();
	int stdfuncallconv get_plugin_list();
	int stdfuncallconv get_plugin_metadata();
	int stdfuncallconv get_plugin_file_path();
	int stdfuncallconv get_plugin_instance();

	int stdfuncallconv register_event_listener();
	int stdfuncallconv register_command();
	int stdfuncallconv register_help_message();
	int stdfuncallconv dispatch_event();

	int stdfuncallconv get_permission_level();
	int stdfuncallconv set_permission_level();

	int stdfuncallconv is_on_executor_thread();
	int stdfuncallconv rcon_query();
};