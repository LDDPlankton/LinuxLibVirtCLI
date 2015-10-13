#include "CommandLineAPI.h"

CommandLineAPI::CommandLineAPI() :
									ipman(this->am.getDB()), osman(this->am.getDB()), ostplman(this->am.getDB()),
									userman(this->am.getDB()), uservpsman(this->am.getDB()), vm(this->am)
{
	//INIT APP MANAGER
	if(!this->am.init())
	{
		exit(1);
	}
	//INITIALIZE + CONNECT TO DB
	this->am.initDB();
}

CommandLineAPI::~CommandLineAPI()
{

}

bool CommandLineAPI::is_exist(string file_or_dir)
{
	struct stat info;
	string dir = file_or_dir;
	if( stat( dir.c_str(), &info ) != 0 )
		return false;
	else
		return true;
}

void CommandLineAPI::printMenu()
{
	cout << "Welcome to LibVirtVM 1.0.0 Main Menu" << endl;
	cout << "IP Management" << endl;
	cout << "\tipadd iptype [IPv4,IPv6] ip \tExample: ipadd IPv4 10.1.1.5;" << endl;
	cout << "\tipdel ip				Example: ipdel 10.1.1.5" << endl;
	cout << "\tiplist\n" << endl;

	cout << "OS Management" << endl;
	cout << "\toslist\n" << endl;

	cout << "User Management" << endl;
	cout << "\tuseradd email password" << endl;
	cout << "\tuserdel email" << endl;
	cout << "\tuserlist\n" << endl;

	cout << "OS Template Management" << endl;
	cout << "\tostpladd name osname path_to_img \tExample: ostpladd Centos65x86 RHEL /usr/local/libvirtvm/images/file.img" << endl;
	cout << "\tostpldel name" << endl;
	cout << "\tostpllist\n" << endl;

	cout << "VPS Management" << endl;
	//cout << "\tvpsadd email ip ostemplate hostname diskspace bandwidth vm_name memory vcpu cpuunits cpupct" << endl;
	cout << "\tvpsadd email ip hostname diskspace bandwidth vmname memory vcpu cpuunits cpupct" << endl;
	cout << "\tvpsosinstall vmname ostpl_name" << endl;
	cout << "\tvpsdel vmname" << endl;
	cout << "\tvpslist" << endl;

}

void CommandLineAPI::run(int argc, char* argv[])
{
	//ENSURE NOT NULL OR STR CONVERSION WILL TERMINATE
	//if(argv[1] == NULL)
	//	argv[1] = "";

	//DECLARE COMMANDS + ARG COUNTER
	string cmds[] = {"ipadd","ipdel","iplist","oslist","useradd","userdel","userlist","ostpladd","ostpldel","ostpllist","vpsadd","vpsosinstall", "vpsdel","vpslist" };
	int argnum[] =  { 2,	  1,	  0,       0,       2,		  1,	    0,         3,		  1,	     0,		     10,	  2,			  1,	   0};
	int cmd = -1;
	string choice( (argv[1])==NULL ? "" : argv[1]);

	//FIND COMMAND INDEX
	for(unsigned int i=0; i < sizeof(cmds)/sizeof(string); i++)
	{
		if(choice == cmds[i])
		{
			cmd = i;
			break;
		}
	}
	//IF NO COMMAND FOUND
	if(cmd == -1)
	{
		this->printMenu();
		//cout << "Unable to find command!" << endl;
		exit(1);
	}
	//ENSURE VALID ARGS ENTERED
	if(argc != argnum[cmd]+2)
	{
		this->printMenu();
		//cout << "Invalid Number of Arguments!" << endl;
		exit(1);
	}

	if(cmds[cmd] == "ipadd")
	{
		string iptype = string(argv[2]);		//ip type
		string ip = string(argv[3]);			//ip

		//VALIDATE
		if(iptype != "IPv4" && iptype != "IPv6")
		{
			cout << "You must specify either IPv4 or IPv6" << endl;
			exit(1);
		}

		//IF EXIST
		if(this->ipman.isIPExist(ip))
		{
			cout << "This IP already exists!" << endl;
			exit(1);
		}

		//ADD IP
		if(this->ipman.addIP(iptype, ip) > 0)
			cout << "IP: " << ip << " added!" << endl;
		else
			cout << this->ipman.getErrorMessage() << endl;
	}
	else if(cmds[cmd] == "ipdel")
	{
		string ip = string(argv[2]);		//ip

		//IF NOT EXIST
		if(!this->ipman.isIPExist(ip))
		{
			cout << "This IP does not exist!" << endl;
			exit(1);
		}

		//GET IP MODEL
		IPListModel model = this->ipman.findByIP(ip);

		//ENSURE IP IS NOT ASSIGNED
		if(model.getVPSID() != 0)
		{
			cout << "This IP is assigned to a VPS!" << endl;
			exit(1);
		}

		//DELETE IP
		if(this->ipman.deleteIP(model))
			cout << "IP: " << ip << " deleted!" << endl;
		else
			cout << this->ipman.getErrorMessage() << endl;

	}
	else if(cmds[cmd] == "iplist")
	{
		list<IPListModel> result = this->ipman.listIPs();

		cout << left << setw(6) << "ID" << setw(10) << "IP_Type" << setw(10) << "IP" << setw(8) << "VPS_ID" << endl;
		cout << "-----------------------------------" << endl;
		for(list<IPListModel>::iterator ii = result.begin(); ii != result.end(); ii++)
		{
			cout << left << setw(6) << (*ii).getID() << setw(10) << (*ii).getIPType() << setw(10) << (*ii).getIP() << setw(8) << (*ii).getVPSID() << endl;
		}
	}
	else if(cmds[cmd] == "oslist")
	{
		list<OSListModel> result = this->osman.listOSs();

		cout << left << setw(6) << "ID" << setw(10) << "Name" << endl;
		cout << "-----------------------------------" << endl;
		for(list<OSListModel>::iterator ii = result.begin(); ii != result.end(); ii++)
		{
			cout << left << setw(6) << (*ii).getID() << setw(10) << (*ii).getName() << endl;
		}
	}
	else if(cmds[cmd] == "useradd")
	{
		string email = string(argv[2]);	//email
		string passwd = string(argv[3]);	//passwd

		//IF EXIST
		if(this->userman.isEmailExist(email))
		{
			cout << "This email address already exists!" << endl;
			exit(1);
		}

		if(this->userman.addUser(email, passwd) > 0)
			cout << "User: " << email << " added!" << endl;
		else
			cout << this->userman.getErrorMessage() << endl;
	}
	else if(cmds[cmd] == "userdel")
	{
		string email = string(argv[2]);	//email

		//IF NOT EXIST
		if(!this->userman.isEmailExist(email))
		{
			cout << "This email address does not exist!" << endl;
			exit(1);
		}

		//GET USER MODEL
		UserModel model = this->userman.findByEmail(email);

		//GET VPS MODEL + CHECK IF USER HAS ANY VPS'S
		UserVPSModel vpsModel;
		vpsModel.setUserID( model.getID() );
		list<UserVPSModel> vpsuserlist = this->uservpsman.findAllBy(vpsModel);
		if(vpsuserlist.size() > 0)
		{
			cout << "You cannot delete this user, as they have VPS's that still exist!" << endl;
			exit(1);
		}

		//DELETE USER
		if(this->userman.deleteUser(model))
		{
			cout << "User: " << email << " deleted!" << endl;
		}
		else
		{
			cout << this->userman.getErrorMessage() << endl;
		}
	}
	else if(cmds[cmd] == "userlist")
	{
		list<UserModel> result = this->userman.listUsers();

		cout << left << setw(6) << "ID" << setw(25) << "Email" << setw(15) << "Time_Created" << endl;
		cout << "--------------------------------------------------------" << endl;
		for(list<UserModel>::iterator ii = result.begin(); ii != result.end(); ii++)
		{
			cout << left << setw(6) << (*ii).getID() << setw(25) << (*ii).getEmail() << setw(15) << (*ii).getTimeCreated() << endl;
		}
	}
	else if(cmds[cmd] == "oslist")
	{
		list<OSListModel> result = this->osman.listOSs();

		cout << left << setw(6) << "ID" << setw(25) << "Name" << endl;
		cout << "--------------------------------------------------------" << endl;
		for(list<OSListModel>::iterator ii = result.begin(); ii != result.end(); ii++)
		{
			cout << left << setw(6) << (*ii).getID() << setw(25) << (*ii).getName() << endl;
		}
	}
	else if(cmds[cmd] == "ostpladd")
	{
		string name = string(argv[2]);	//name
		string osname = string(argv[3]);	//name
		string img = string(argv[4]);	//path to img
		if(!this->is_exist(img))
		{
			cout << "Error:: Image " << img << " does not exist!" << endl;
			exit(1);
		}

		//IF EXIST
		if(this->ostplman.isTemplateNameExist(name))
		{
			cout << "This OS Template Name exists!" << endl;
			exit(1);
		}
		//IF NOT EXIST
		if(!this->osman.isOSNameExist(osname))
		{
			cout << "This OS Name does not exist" << endl;
			exit(1);
		}

		//GET OS MODEL INFO
		OSListModel omodel = this->osman.findByOSName(osname);

		//ADD OS TEMPLATE
		if(this->ostplman.addOSTemplate(omodel.getID(), name, img) > 0)
			cout << "OS Template: " << img << " added!" << endl;
		else
			cout << this->ostplman.getErrorMessage() << endl;
	}
	else if(cmds[cmd] == "ostpldel")
	{
		string name = string(argv[2]);	//name

		//IF NOT EXIST
		if(!this->ostplman.isTemplateNameExist(name))
		{
			cout << "This template name does not exist!" << endl;
			exit(1);
		}

		OSTemplateModel model = this->ostplman.findByTemplateName(name);
		if(this->ostplman.deleteOSTemplate(model))
			cout << "OS Template: " << name << " deleted!" << endl;
		else
			cout << this->ostplman.getErrorMessage() << endl;
	}
	else if(cmds[cmd] == "ostpllist")
	{
		list<OSTemplateModel> result = this->ostplman.listTemplates();
		cout << left << setw(6) << "ID" << setw(25) << "Name" << setw(15) << "Path" << endl;
		cout << "--------------------------------------------------------" << endl;
		for(list<OSTemplateModel>::iterator ii = result.begin(); ii != result.end(); ii++)
		{
			cout << left << setw(6) << (*ii).getID() << setw(25) << (*ii).getName() << setw(15) << (*ii).getTemplatePath() << endl;
		}
	}
	else if(cmds[cmd] == "vpsadd")
	{
		string email = string(argv[2]);						//email
		string ip = string(argv[3]);						//ip
		//string os_template = string(argv[4]);				//os template
		string hostname = string(argv[4]);					//hostname
		int diskspace = strhelper.toInt(argv[5]);			//diskspace
		int bandwidth = strhelper.toInt(argv[6]);			//bandwidth
		string vmname = string(argv[7]);					//vmname
		int memory = strhelper.toInt(argv[8]);				//memory
		int vcpu = strhelper.toInt(argv[9]);				//vcpu
		int cpuunits = strhelper.toInt(argv[10]);			//cpuunits
		int cpupct = strhelper.toInt(argv[11]);				//cpupct

		//ENSURE VALID DATA
		if(email == "" || ip == "" || hostname == "" || diskspace <=0 || bandwidth <= 0 || vmname == "" || memory <= 0 || vcpu <= 0 || cpuunits <= 0 || cpupct <= 0)
		{
			cout << "You must specify valid params that are not blank or <= 0!" << endl;
			exit(1);
		}
		if(diskspace < 5)
		{
			cout << "You must specify 5GB or more of diskspace!" << endl;
			exit(1);
		}
		if(memory < 64)
		{
			cout << "You must specify 64MB or more of memory!" << endl;
			exit(1);
		}

		//IF VM NAME ALREADY EXISTS
		if(this->uservpsman.isVMNameExist(vmname))
		{
			cout << "This VM Name already exists!" << endl;
			exit(1);
		}

		//IF EMAIL NOT EXIST
		if(!this->userman.isEmailExist(email))
		{
			cout << "This email address does not exist!" << endl;
			exit(1);
		}

		//IF IP NOT EXIST
		if(!this->ipman.isIPExist(ip))
		{
			cout << "This IP does not exist!" << endl;
			exit(1);
		}

		//FIND USER_ID
		UserModel umodel = this->userman.findByEmail(email);
		int user_id = umodel.getID();
		int vps_id = -1;

		//FIND IP
		IPListModel lmodel = this->ipman.findByIP(ip);

		//ENSURE IP NOT ASSIGNED TO SOMEONE ELSE
		if(lmodel.getVPSID() > 0)
		{
			cout << "This IP is assigned to another VPS!" << endl;
			exit(1);
		}

		//ADD VPS
		if( (vps_id=this->uservpsman.addVPS(user_id, hostname, diskspace, bandwidth, vmname, memory, vcpu, cpuunits, cpupct)) > 0)
		{
			//UPDATE IP WITH VPS_ID
			lmodel.setVPSID(vps_id);
			if(!this->ipman.update(lmodel))
			{
				cout << this->ipman.getErrorMessage() << endl;
			}

			//CREATE VM
			string libvirt_name = "vm"+strhelper.toString(vps_id);
			if(vm.createVM(libvirt_name, diskspace, memory, vcpu, "LVMG42", ip))
					cout << "VPS: " << vmname << " added!" << endl;
			else
				cout << vm.getErrorMessage() << endl;
		}
		else
			cout << this->userman.getErrorMessage() << endl;

	}
	else if(cmds[cmd] == "vpsosinstall")
	{
		string vmname = string(argv[2]);			//vmname
		string ostpl_name = string(argv[3]);		//os template name

		//IF OS TEMPLATE DOES NOT EXIST
		if(!this->ostplman.isTemplateNameExist(ostpl_name))
		{
			cout << "This OS Template does not exist!" << endl;
			exit(1);
		}

		//IF VM NAME DOES NOT EXIST
		if(!this->uservpsman.isVMNameExist(vmname))
		{
			cout << "This VM Name does not exist!" << endl;
			exit(1);
		}

		//GET OS TEMPLATE MODEL
		OSTemplateModel omodel = this->ostplman.findByTemplateName(ostpl_name);

		//GET USERVPS MODEL + SET OS + UPDATE
		UserVPSModel uvmodel = this->uservpsman.findByVMName(vmname);
		uvmodel.setVMOSID(omodel.getOSID());
		if(!this->uservpsman.update(uvmodel))
			cout << this->uservpsman.getErrorMessage() << endl;

		//ENSURE IMG EXISTS
		if(!this->is_exist(omodel.getTemplatePath()))
		{
			cout << "Error:: Image " << omodel.getTemplatePath() << " does not exist!" << endl;
			exit(1);
		}

		//INSTALL OS
		string libvirt_name = "vm"+strhelper.toString(uvmodel.getID());
		if(vm.installOSVM(libvirt_name, "LVMG42", omodel.getTemplatePath() ))
		{
			cout << "OS: " << vmname << " installed!" << endl;
		}
		else
			cout << vm.getErrorMessage() << endl;
	}
	else if(cmds[cmd] == "vpsdel")
	{
		string vmname = string(argv[2]);	//vmname

		//IF USER VPS NOT EXIST
		if(!this->uservpsman.isVMNameExist(vmname))
		{
			cout << "This VPS name does not exist!" << endl;
			exit(1);
		}

		//FIND VPS INFO
		UserVPSModel vmodel = this->uservpsman.findByVMName(vmname);

		//FIND ALL IPS BY VPS_ID
		IPListModel fipmodel;
		fipmodel.setVPSID(vmodel.getID());
		list<IPListModel> ipresult = this->ipman.findAllBy(fipmodel);
		for(list<IPListModel>::iterator ii = ipresult.begin(); ii != ipresult.end(); ii++)
		{
			//UPDATE IP VPS_ID
			IPListModel tmp = (*ii);
			tmp.setVPSID(0);
			if(!this->ipman.update(tmp))
				cout << this->ipman.getErrorMessage() << endl;
		}

		//DELETE VM FROM DB
		if(!this->uservpsman.deleteVPS(vmodel))
		{
			cout << this->uservpsman.getErrorMessage() << endl;
			exit(1);
		}

		//DELETE VM FROM SERVER + LVG
		string libvirt_name = "vm"+strhelper.toString(vmodel.getID());
		if(vm.deleteVM(libvirt_name, "LVMG42"))
			cout << "VM: " << vmname << " deleted!" << endl;
		else
			cout << vm.getErrorMessage() << endl;

	}
	else if(cmds[cmd] == "vpslist")
	{
		list<UserVPSModel> result = this->uservpsman.listVPSs();

		cout << left << setw(6) << "ID" << setw(25) << "VM_NAME" << setw(15) << "OS_ID" << setw(15) << "USER_ID" << endl;
		cout << "--------------------------------------------------------" << endl;
		for(list<UserVPSModel>::iterator ii = result.begin(); ii != result.end(); ii++)
		{
			cout << left << setw(6) << (*ii).getID() << setw(25) << (*ii).getVMName() << setw(15) << (*ii).getVMOSID() << setw(15) << (*ii).getUserID() << endl;
		}
	}



}
