#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>

#include "CommandLineAPI.h"
#include "Core/AppManager.h"
#include "Core/VirtManager.h"
#include "Install/Install.h"
#include "Install/Upgrade.h"

using namespace std;

void checkSystem()
{
	//CREATE APP MANAGER + VIRT MANAGER
	AppManager *am = new AppManager();

	//CHECK IF INSTALLED
	Install ins(*am);

	//IF NOT INSTALLED RUN INSTALLER
	if(!ins.is_installed())
	{
		ins.run_installer();
		delete(am);
		exit(1);
	}
	delete(am);
}

int main(int argc, char* argv[])
{
	//HANDLE INSTALL/UPGRADE
	checkSystem();

	CommandLineAPI cmd;
	cmd.run(argc, argv);

	return 0;
}

