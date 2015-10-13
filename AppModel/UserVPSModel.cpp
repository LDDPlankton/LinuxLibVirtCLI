#include "UserVPSModel.h"

UserVPSModel::UserVPSModel()
{
	this->id = 0;
	this->user_id = 0;
	this->vm_os_id = 0;
	this->vm_hostname = "";
	this->vm_diskspace = 0;
	this->vm_bandwidth = 0;
	this->vm_name = "";
	this->vm_memory = 0;
	this->vm_vcpu = 0;
	this->vm_cpuunits = 0;
	this->vm_cpupct = 0;
	this->vm_enable_vnc = 0;
}

UserVPSModel::~UserVPSModel()
{

}

bool UserVPSModel::setData(map<string,string> newdata)
{
	this->id = this->strhelper.toInt( newdata["id"] );
	this->user_id = this->strhelper.toInt(newdata["user_id"] );
	this->vm_os_id = this->strhelper.toInt(newdata["vm_os_id"] );
	this->vm_hostname = newdata["vm_hostname"];
	this->vm_diskspace = this->strhelper.toInt( newdata["vm_diskspace"] );
	this->vm_bandwidth = this->strhelper.toInt( newdata["vm_bandwidth"] );
	this->vm_name = newdata["vm_name"];
	this->vm_memory = this->strhelper.toInt( newdata["vm_memory"] );
	this->vm_vcpu = this->strhelper.toInt( newdata["vm_vcpu"] );
	this->vm_cpuunits = this->strhelper.toInt( newdata["vm_cpuunits"] );
	this->vm_cpupct = this->strhelper.toInt( newdata["vm_cpupct"] );
	this->vm_enable_vnc = this->strhelper.toInt( newdata["vm_enable_vnc"] );
	return true;
};

map<string,string> UserVPSModel::getData()
{
	return this->data;
}

void UserVPSModel::setID(int s) { this->id = s; }
void UserVPSModel::setUserID(int s) { this->user_id = s; }
void UserVPSModel::setVMOSID(int s) { this->vm_os_id = s; }
void UserVPSModel::setVMHostName(string s) { this->vm_hostname = s; }
void UserVPSModel::setVMDiskSpace(int s) { this->vm_diskspace = s; }
void UserVPSModel::setVMBandwidth(int s) { this->vm_bandwidth = s; }
void UserVPSModel::setVMName(string s) { this->vm_name = s; }
void UserVPSModel::setVMMemory(int s) { this->vm_memory = s; }
void UserVPSModel::setVMVcpu(int s) { this->vm_vcpu = s; }
void UserVPSModel::setVMCpuUnits(int s) { this->vm_cpuunits = s; }
void UserVPSModel::setVMCpuPct(int s) { this->vm_cpupct = s; }
void UserVPSModel::setVMEnableVNC(int s) { this->vm_enable_vnc = s; }

int UserVPSModel::getID() { return this->id; }
int UserVPSModel::getUserID() { return this->user_id; }
int UserVPSModel::getVMOSID() { return this->vm_os_id; }
string UserVPSModel::getVMHostName() { return this->vm_hostname; }
int UserVPSModel::getVMDiskSpace() { return this->vm_diskspace; }
int UserVPSModel::getVMBandwidth() { return this->vm_bandwidth; }
string UserVPSModel::getVMName() { return this->vm_name; }
int UserVPSModel::getVMMemory() { return this->vm_memory; }
int UserVPSModel::getVMVcpu() { return this->vm_vcpu; }
int UserVPSModel::getVMCpuUnits() { return this->vm_cpuunits; }
int UserVPSModel::getVMCpuPct() { return this->vm_cpupct; }
int UserVPSModel::getVMEnableVNC() { return this->vm_enable_vnc; }

