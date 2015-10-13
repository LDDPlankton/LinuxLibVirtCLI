#include "VirtManager.h"

VirtManager::VirtManager(AppManager &app_man) : app_man(app_man)
{
	if( this->app_man.getVirtType() == "KVM" )
	{
		//this->virt_interface = new() ... add on interface creating in nxt vers;
		if(!this->virt_interface.connect())
		{
			cout << "Error: " << this->virt_interface.getErrorMessage() << endl;
			exit(1);
		}
	}
}

VirtManager::~VirtManager()
{

}

string VirtManager::getErrorMessage()
{
	return this->error_message;
}

/*
 * This function will restart the libvirtd service
 *
 * @return bool
 */
bool VirtManager::restartLibVirtd()
{
	this->app_man.getCommandExecutor().addCommand("service libvirtd restart", 0);
	this->app_man.getCommandExecutor().runCommand();

	//CHECK IF COMMAND RAN OK
	if(!this->app_man.getCommandExecutor().getCommandStatus())
	{
		this->error_message = "Unable to restart libvirtd! => " + this->app_man.getCommandExecutor().getOutput();
		return false;
	}
	return true;
}

/*
 * This function will create a VM [DB, LVM, LibVirt]
 *
 * @param string vmname
 * @param int disk_space
 * @param int memory
 * @param int vcpu
 * @param lvg
 * @param ip
 * @return bool
 */
bool VirtManager::createVM(string vmname, int disk_space, int memory, int vcpu, string lvg, string ip)
{
	StringHelper strh;

	//GENERATE MAC
	srand (time(NULL));
	string macv_field = "ABCDEF1234567890";
	string mac = "00:22:62:";
	mac += macv_field[rand() % 15 + 1];
	mac += macv_field[rand() % 15 + 1];
	mac += ":";
	mac += macv_field[rand() % 15 + 1];
	mac += macv_field[rand() % 15 + 1];
	mac += ":";
	mac += macv_field[rand() % 15 + 1];
	mac += macv_field[rand() % 15 + 1];

	//STEP #1. GENERATE XML CONFIG
	//SET VIRT VARIABLES
	string LVM = "/dev/" + lvg + "/" + vmname;
	this->app_man.getConfigLoader().setVariable("VM_NAME", vmname );
	this->app_man.getConfigLoader().setVariable("VM_MEMORY", strh.toString(memory*(1024)) );
	this->app_man.getConfigLoader().setVariable("VM_VCPU", strh.toString(vcpu) );
	this->app_man.getConfigLoader().setVariable("VM_LVG", LVM );
	this->app_man.getConfigLoader().setVariable("VM_IP", ip );
	this->app_man.getConfigLoader().setVariable("VM_MACADDR", mac );
	this->app_man.getConfigLoader().setBlock("VNC_BLOCK", "<graphics type='vnc' port='-1' passwd='' listen='0.0.0.0'/>");

	//CONVERT XML CONFIG + CLEAN IT
	string newstr = this->app_man.getConfigLoader().getXMLConfig();
	strh.trim(newstr);
	const char *xmlconfig = newstr.c_str();

	//STEP #2. CREATE LIBVIRT CONFIG FILE
	bool st_status = this->virt_interface.createVM(xmlconfig);
	if(!st_status)
	{
		this->error_message = "Error:: VirtManager::createVM() => " + this->virt_interface.getErrorMessage();
		return false;
	}

	//STEP #3. CREATE LVM PARTITION
	bool part_status = this->app_man.getLVMManager().createLogicalPartition(vmname, strh.toString(disk_space) + "G", lvg);
	if(!part_status)
	{
		this->error_message = "Error:: VirtManager::createVM() => " + this->app_man.getLVMManager().getMessage();
		return false;
	}

	//STEP #4. RESTART LIBVIRTD SERVICE
	bool status = this->restartLibVirtd();
	if(!status)
	{
		this->error_message = "Error:: VirtManager::createVM() => " + this->error_message;
		return false;
	}

	return true;
}

/*
 * This function will delete a vm [DB, LVM, LibVirt]
 *
 * @param string vmname
 * @param string lvg
 * @return bool
 */
bool VirtManager::deleteVM(string vmname, string lvg)
{
	//STEP #1. SHUTDOWN VM
	bool st_status = this->virt_interface.stopVM(vmname);
	if(!st_status)
	{
		//cout << "Warning:: VirtManager::deleteVM() 1 => " << this->virt_interface.getErrorMessage() << endl;
	}

	//STEP #2. DELETE LIBVIRT FILE FOR THIS VM
	bool vi_status = this->virt_interface.deleteVM(vmname);
	if(!vi_status)
	{
		this->error_message = "Error:: VirtManager::deleteVM() => " + this->virt_interface.getErrorMessage();
		return false;
	}

	//STEP #3. DELETE LVM PARTITION
	bool part_status = this->app_man.getLVMManager().removeLogicalPartition(vmname, lvg);
	if(!part_status)
	{
		this->error_message = "Error:: VirtManager::deleteVM() => " + this->app_man.getLVMManager().getMessage();
		return false;
	}

	//STEP #4. RESTART LIBVIRTD SERVICE
	bool status = this->restartLibVirtd();
	if(!status)
	{
		this->error_message = "Error:: VirtManager::deleteVM() => " + this->error_message;
		return false;
	}

	return true;
}

/*
 * This function will install/reinstall an OS from a image file onto a particular VM
 *
 * @param string vmname
 * @param string os_file_template
 * @return bool
 */
bool VirtManager::installOSVM(string vmname, string lvg, string os_file_template)
{
	struct stat info;
	string dir = os_file_template;
	if( stat( dir.c_str(), &info ) != 0 )
	{
		this->error_message = "Error:: VirtManager:installOSVM() => The OS File Template does not exist!";
		return false;
	}

	//STEP #4. COPY OS TEMPLATE TO LVM PARTITION
	string LVM = "/dev/" + lvg + "/" + vmname;
	string command = "dd bs=1M if=" + os_file_template + " of=" + LVM;
	this->app_man.getCommandExecutor().addCommand(command, 0);
	this->app_man.getCommandExecutor().runCommand();

	//CHECK IF COMMAND RAN OK
	if(!this->app_man.getCommandExecutor().getCommandStatus())
	{
		this->error_message = "Error:: VirtManager:installOSVM() => " + this->app_man.getCommandExecutor().getOutput();
		return false;
	}
	return true;
}
