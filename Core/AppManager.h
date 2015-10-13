#ifndef APPMANAGER_H_
#define APPMANAGER_H_

#include <iostream>
#include <libvirt/libvirt.h>
#include "../ConfigLoader/ConfigLoader.h"
#include "CommandExecutor/CommandExecutor.h"
#include "../LVM/LVMManager.h"
#include "SQLite/SQLite.h"
using namespace std;

class AppManager
{
public:
	AppManager();
	~AppManager();
	bool init();
	void initDB();
	void printSystemDebug();
	string getVirtType();
	SQLite& getDB();
	ConfigLoader& getConfigLoader();
	CommandExecutor& getCommandExecutor();
	LVMManager& getLVMManager();

private:
	string virt_type;
	ConfigLoader config_loader;
	CommandExecutor command_exec;
	LVMManager logical_vmm;
	SQLite db;
};

#endif
