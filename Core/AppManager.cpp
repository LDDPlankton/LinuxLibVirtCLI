#include "AppManager.h"

AppManager::AppManager()
{
	this->virt_type = "KVM";
}

AppManager::~AppManager()
{
	this->db.closeDatabase();
}

bool AppManager::init()
{
	if(this->virt_type == "KVM")
		return this->config_loader.loadConfig("KVM");
	return false;
}

void AppManager::initDB()
{
	bool status = this->db.setDatabase("/usr/local/libvirtvm/data.db");
	if(!status)
	{
		cout << "Failed to Set Database!" << endl;
		exit(1);
	}

	status = this->db.openDatabase();
	if(!status)
	{
		cout << "Failed to Open Database!" << endl;
		exit(1);
	}
}

void AppManager::printSystemDebug()
{
	virConnectPtr conn;
	char *host;
	int vcpus;
	virNodeInfo nodeinfo;
	unsigned long ver;
	unsigned long long node_free_memory;

	conn = virConnectOpen("qemu:///system");

	host = virConnectGetHostname(conn);
	cout << "Hostname: " << host << endl;
	delete host;

    vcpus = virConnectGetMaxVcpus(conn, NULL);
    cout << "Maximum support virtual CPUs: " << vcpus << endl;

    node_free_memory = virNodeGetFreeMemory(conn);
    cout << "Node free memory: " << node_free_memory << endl;

    virNodeGetInfo(conn, &nodeinfo);

    cout << "Model: " << nodeinfo.model << endl;
    cout << "Memory size: " << nodeinfo.memory << endl;
    cout << "Number of CPUs: " << nodeinfo.cpus << endl;
    cout << "MHz of CPUs: " << nodeinfo.mhz << endl;
    cout << "Number of NUMA nodes: " << nodeinfo.nodes << endl;
    cout << "Number of CPU sockets: " << nodeinfo.sockets << endl;
    cout << "Number of CPU cores per socket: " << nodeinfo.cores << endl;
    cout << "Number of CPU threads per core: " << nodeinfo.threads << endl;

    cout << "Virtualization type: " << virConnectGetType(conn) << endl;

    virConnectGetLibVersion(conn, &ver);
    cout << "Libvirt Version: " << ver << endl;

    virConnectClose(conn);
}

string AppManager::getVirtType()
{
	return this->virt_type;
}

SQLite& AppManager::getDB()
{
	return this->db;
}

ConfigLoader& AppManager::getConfigLoader()
{
	return this->config_loader;
}

CommandExecutor& AppManager::getCommandExecutor()
{
	return this->command_exec;
}

LVMManager& AppManager::getLVMManager()
{
	return this->logical_vmm;
}

