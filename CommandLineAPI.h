#ifndef COMMANDLINEAPI_H_
#define COMMANDLINEAPI_H_

extern "C"
{
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <unistd.h>
}

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <list>
#include <string>
#include "AppLib/IPMan.h"
#include "AppLib/OSTemplateMan.h"
#include "AppLib/OSMan.h"
#include "AppLib/UserMan.h"
#include "AppLib/UserVPSMan.h"
#include "AppModel/IPListModel.h"
#include "AppModel/OSTemplateModel.h"
#include "AppModel/UserModel.h"
#include "AppModel/UserVPSModel.h"
#include "Core/AppManager.h"
#include "Core/VirtManager.h"
#include "Helpers/StringHelper.h"
using namespace std;

class CommandLineAPI
{
public:
	CommandLineAPI();
	~CommandLineAPI();
	bool is_exist(string file_or_dir);
	void printMenu();
	void run(int argc, char* argv[]);

private:
	StringHelper strhelper;
	AppManager am;
	IPMan ipman;
	OSMan osman;
	OSTemplateMan ostplman;
	UserMan userman;
	UserVPSMan uservpsman;
	VirtManager vm;
};

#endif
