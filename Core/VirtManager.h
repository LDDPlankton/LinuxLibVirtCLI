#ifndef VIRTMANAGER_H_
#define VIRTMANAGER_H_

extern "C"
{
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <unistd.h>
}

#include <cstdlib>
#include "AppManager.h"
#include "../Virtualization/KVM.h"
#include "Helpers/MiscTool.h"
using namespace std;

class VirtManager
{
public:
	VirtManager(AppManager &app_man);
	~VirtManager();
	string getErrorMessage();
	bool restartLibVirtd();
	bool createVM(string vmname, int disk_space, int memory, int vcpu, string lvg, string ip);
	bool deleteVM(string vmname, string lvg);
	bool installOSVM(string vmname, string lvg, string os_file_template);

private:
	string error_message;
	AppManager &app_man;
	KVM virt_interface;			//DO: Not yet an interface, fix when Xen/OpenVZ added
};

#endif
