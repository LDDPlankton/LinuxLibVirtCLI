#include "Install.h"

Install::Install(AppManager &app_man) : app_man(app_man)
{
	this->version = "1.0.0";
}

Install::~Install()
{


}

/*
 * This function contains all the SQL directives for our installer
 *
 * @return bool
 */
bool Install::runSQL(string lvm_drive)
{
	//NOW CREATE SQL
	string sql1 = "CREATE TABLE config_settings ("
	   "id    INTEGER PRIMARY KEY AUTOINCREMENT,"
	   "[key] TEXT,"
	   "value TEXT);";

	string sql2 = "CREATE TABLE os_templates ("
		"id            INTEGER         PRIMARY KEY AUTOINCREMENT,"
		"os_id         INTEGER,"
		"name          VARCHAR( 255 ),"
		"template_path VARCHAR( 255 )"
		");";

	string sql3 = "CREATE TABLE user_vps ("
	    "id            INTEGER         PRIMARY KEY AUTOINCREMENT,"
	    "user_id       INTEGER( 25 )   REFERENCES users ( id ),"
	    "vm_os_id      INTEGER( 1 ),"
	    "vm_hostname   VARCHAR( 255 ),"
	    "vm_diskspace  INTEGER( 5 ),"
	    "vm_bandwidth  INTEGER( 5 ),"
	    "vm_name       VARCHAR( 255 ),"
	    "vm_memory     INTEGER( 10 ),"
	    "vm_vcpu       INTEGER( 5 ),"
	    "vm_cpuunits   INTEGER( 10 ),"
	    "vm_cpupct     INTEGER( 5 ),"
	    "vm_enable_vnc INTEGER( 1 )"
		");";

	string sql4 = "CREATE TABLE users ("
			"id           INTEGER         PRIMARY KEY AUTOINCREMENT,"
			"email        VARCHAR( 255 ),"
			"password     VARCHAR( 255 ),"
			"time_created DATETIME"
			");";

	string sql5 = "CREATE TABLE ip_list ("
			"id      INTEGER         PRIMARY KEY AUTOINCREMENT,"
			"vps_id  INTEGER,"
			"ip_type VARCHAR( 4 ),"
			"ip      VARCHAR( 255 )"
			");";

	string sql6 = "CREATE TABLE os_list ("
			"id   INTEGER         PRIMARY KEY AUTOINCREMENT,"
			"name VARCHAR( 255 )"
			");";

	string sql7 = "INSERT INTO `config_settings` (`key`,`value`) VALUES (?, ?);";
	string sql8 = "INSERT INTO `config_settings` (`key`,`value`) VALUES (?, ?);";
	string sql9 = "INSERT INTO `os_list` (`name`) VALUES (?);";
	string sql10 = "INSERT INTO `os_list` (`name`) VALUES (?);";
	string sql11 = "INSERT INTO `os_list` (`name`) VALUES (?);";

	//INITIALIZE + CONNECT TO DB
	this->app_man.initDB();

	cout << "Now running SQL Queries ..." << endl;

	//QUERY 1
	bool status = this->app_man.getDB().setQuery(sql1);
	status = this->app_man.getDB().runQuery();
	if( !this->app_man.getDB().getQueryStatus() )
	{
		cout << "SQL Error: " << this->app_man.getDB().getErrorMessage() << endl;
		return false;
	}
	//QUERY 2
	this->app_man.getDB().setQuery(sql2);
	this->app_man.getDB().runQuery();
	if( !this->app_man.getDB().getQueryStatus() )
	{
		cout << "SQL Error: " << this->app_man.getDB().getErrorMessage() << endl;
		return false;
	}
	//QUERY 3
	this->app_man.getDB().setQuery(sql3);
	this->app_man.getDB().runQuery();
	if( !this->app_man.getDB().getQueryStatus() )
	{
		cout << "SQL Error: " << this->app_man.getDB().getErrorMessage() << endl;
		return false;
	}
	//QUERY 4
	this->app_man.getDB().setQuery(sql4);
	this->app_man.getDB().runQuery();
	if( !this->app_man.getDB().getQueryStatus() )
	{
		cout << "SQL Error: " << this->app_man.getDB().getErrorMessage() << endl;
		return false;
	}
	//QUERY 5
	this->app_man.getDB().setQuery(sql5);
	this->app_man.getDB().runQuery();
	if( !this->app_man.getDB().getQueryStatus() )
	{
		cout << "SQL Error: " << this->app_man.getDB().getErrorMessage() << endl;
		return false;
	}
	//QUERY 6
	this->app_man.getDB().setQuery(sql6);
	this->app_man.getDB().runQuery();
	if( !this->app_man.getDB().getQueryStatus() )
	{
		cout << "SQL Error: " << this->app_man.getDB().getErrorMessage() << endl;
		return false;
	}
	//QUERY 7
	this->app_man.getDB().setQuery(sql7);
	this->app_man.getDB().setParamText("VERSION");
	this->app_man.getDB().setParamText("1.0.0");
	this->app_man.getDB().runQuery();
	if( !this->app_man.getDB().getQueryStatus() )
	{
		cout << "SQL Error: " << this->app_man.getDB().getErrorMessage() << endl;
		return false;
	}
	//QUERY 8
	this->app_man.getDB().setQuery(sql8);
	this->app_man.getDB().setParamText("LVMG42");
	this->app_man.getDB().setParamText(lvm_drive);
	this->app_man.getDB().runQuery();
	if( !this->app_man.getDB().getQueryStatus() )
	{
		cout << "SQL Error: " << this->app_man.getDB().getErrorMessage() << endl;
		return false;
	}
	//QUERY 9
	this->app_man.getDB().setQuery(sql9);
	this->app_man.getDB().setParamText("RHEL");
	this->app_man.getDB().runQuery();
	if( !this->app_man.getDB().getQueryStatus() )
	{
		cout << "SQL Error: " << this->app_man.getDB().getErrorMessage() << endl;
		return false;
	}
	//QUERY 10
	this->app_man.getDB().setQuery(sql10);
	this->app_man.getDB().setParamText("FreeBSD");
	this->app_man.getDB().runQuery();
	if( !this->app_man.getDB().getQueryStatus() )
	{
		cout << "SQL Error: " << this->app_man.getDB().getErrorMessage() << endl;
		return false;
	}
	//QUERY 11
	this->app_man.getDB().setQuery(sql11);
	this->app_man.getDB().setParamText("Windows");
	this->app_man.getDB().runQuery();
	if( !this->app_man.getDB().getQueryStatus() )
	{
		cout << "SQL Error: " << this->app_man.getDB().getErrorMessage() << endl;
		return false;
	}

	return true;
}

/*
 * This function will copy our system config to our libvirtvm install directory.
 *
 * @return bool
 */
bool Install::copy_config()
{
	//COPY KVM CONFIG
	cout << "Now generating KVM Config File ..." << endl;
	KVMConfig config;
	string myconfig = config.generateConfig();
	ofstream out("/usr/local/libvirtvm/config/virt_kvm_config.txt");
	out << myconfig;
	out.close();
	return true;
}

/*
 * This function will check to see if the install location already exist or not
 *
 * @param bool
 */
bool Install::is_installed()
{
	struct stat info;
	string dir = "/usr/local/libvirtvm";
	if( stat( dir.c_str(), &info ) != 0 )
		return false;
	else
		return true;
}

/*
 * This function is the main installer function to install our virtualization system.
 *
 * @return bool
 */
bool Install::run_installer()
{
	string lvm_drive = "";													//LOCATION FOR OUR VMS
	string confirm = "";
	string command = "";

	cout << "-----LibVirtVM Installer Version " << this->version << endl;
	cout << "Step #1. Setup LVM Partition" << endl;
	cout << "Enter Physical Volume Path [/dev/sdb1, etc]:" << endl;
	cin >> lvm_drive;
	this->strutil.trim(lvm_drive);

	//GET DRIVE PATH + CONFIRM CHOICE
	while(true)
	{
		cout << "Confirm: Run 'pvcreate' on [" << lvm_drive << "] [Y/N]: " << endl;
		cin >> confirm;
		if(confirm == "Y" || confirm == "y")
			break;
		else
		{
			cout << "Enter Physical Volume Path [/dev/sdb1, etc]:" << endl;
			cin >> lvm_drive;
			this->strutil.trim(lvm_drive);
		}
	}

	//CREATE LVM PARTITION
	cout << "Running PVCreate ..." << endl;
	command = "pvcreate " + lvm_drive;
	this->app_man.getCommandExecutor().addCommand(command, 0);
	this->app_man.getCommandExecutor().runCommand();

	//CHECK IF COMMAND RAN OK
	if(!this->app_man.getCommandExecutor().getCommandStatus())
	{
		cout << "Error:: Unable to create libvirtvm directory! => " << this->app_man.getCommandExecutor().getOutput() << endl;
		return false;
	}

	//CREATE VOLUME GROUP
	cout << "Running VGCreate ..." << endl;
	command = "vgcreate LVMG42 " + lvm_drive;
	this->app_man.getCommandExecutor().addCommand(command, 0);
	this->app_man.getCommandExecutor().runCommand();

	//CHECK IF COMMAND RAN OK
	if(!this->app_man.getCommandExecutor().getCommandStatus())
	{
		cout << "Error:: Unable to create volume group! => " << this->app_man.getCommandExecutor().getOutput() << endl;
		return false;
	}

	//CREATE LIBVIRTVM DIRECTORY
	cout << "Creating System Directories ..." << endl;
	this->app_man.getCommandExecutor().addCommand("mkdir /usr/local/libvirtvm", 0);
	this->app_man.getCommandExecutor().addCommand("mkdir /usr/local/libvirtvm/os_images", 0);
	this->app_man.getCommandExecutor().addCommand("mkdir /usr/local/libvirtvm/config", 0);
	this->app_man.getCommandExecutor().runCommand();

	//CHECK IF COMMAND RAN OK
	if(!this->app_man.getCommandExecutor().getCommandStatus())
	{
		cout << "Error:: Unable to create libvirtvm directory! => " << this->app_man.getCommandExecutor().getOutput() << endl;
		return false;
	}

	//RUN SQL
	bool status = this->runSQL(lvm_drive);
	if(!status)
		return false;

	//RUN COPY CONFIG
	status = this->copy_config();
	if(!status)
		return false;

	cout << "Installation Complete. Please run program again to access menu options." << endl;

	return true;

}
