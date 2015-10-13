#ifndef INSTALL_H_
#define INSTALL_H_

#include <iostream>
#include <fstream>
#include <iostream>
#include "KVMConfig.h";
#include "../Core/AppManager.h"
#include "Helpers/StringHelper.h"
extern "C"
{
	#include <sys/types.h>
	#include <sys/stat.h>
}
using namespace std;

class Install
{
public:
	Install(AppManager &app_man);
	~Install();
	bool runSQL(string lvm_drive);
	bool copy_config();
	bool is_installed();
	bool run_installer();

private:
	AppManager &app_man;
	string version;
	StringHelper strutil;
};

#endif
