#ifndef USERVPSMODEL_H_
#define USERVPSMODEL_H_

#include <iostream>
#include <map>
#include "Helpers/StringHelper.h"
using namespace std;

class UserVPSModel
{
public:
	UserVPSModel();
	~UserVPSModel();
	bool setData(map<string,string> newdata);
	map<string,string> getData();

	void setID(int s);
	void setUserID(int s);
	void setVMOSID(int s);
	void setVMHostName(string s);
	void setVMDiskSpace(int s);
	void setVMBandwidth(int s);
	void setVMName(string s);
	void setVMMemory(int s);
	void setVMVcpu(int s);
	void setVMCpuUnits(int s);
	void setVMCpuPct(int s);
	void setVMEnableVNC(int s);

	int getID();
	int getUserID();
	int getVMOSID();
	string getVMHostName();
	int getVMDiskSpace();
	int getVMBandwidth();
	string getVMName();
	int getVMMemory();
	int getVMVcpu();
	int getVMCpuUnits();
	int getVMCpuPct();
	int getVMEnableVNC();

private:
	map<string,string> data;
	StringHelper strhelper;
	int id;
	int user_id;
	int vm_os_id;
	string vm_hostname;
	int vm_diskspace;
	int vm_bandwidth;
	string vm_name;
	int vm_memory;
	int vm_vcpu;
	int vm_cpuunits;
	int vm_cpupct;
	int vm_enable_vnc;
};

#endif
