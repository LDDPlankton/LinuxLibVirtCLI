#ifndef LVMMANAGER_H_
#define LVMMANAGER_H_

#include <iostream>
#include <map>
#include "Helpers/MiscTool.h"
#include "CommandExecutor/CommandExecutor.h"
#include "LVMCore.h"

class LVMManager
{
public:
	LVMManager()
	{
		this->message = "";
	}
	~LVMManager()
	{

	}

	std::string getMessage()
	{
		return this->message;
	}

	//lvcreate -n vs1001 --size 30M SVM_1
	bool createLogicalPartition(std::string lv_name, std::string lv_size, std::string volume_group)
	{
		std::string command = "lvcreate";
		if(lv_size.find("G") == std::string::npos)
		{
			return false;
		}
		std::map<std::string,std::string> tmp_map;
		tmp_map.insert( std::pair<std::string,std::string>("-n",lv_name) );
		tmp_map.insert( std::pair<std::string,std::string>("--size",lv_size) );
		tmp_map.insert( std::pair<std::string,std::string>(volume_group,"") );
		command += " " + miscTool.mapToString(tmp_map);
		//std::cout << "CLP: [" << command << "]" << std::endl;

		//RUN COMMANDS
		commandExecutor.addCommand(command, 0);
		commandExecutor.runCommand();

		//CHECK IF COMMAND RAN OK
		if(commandExecutor.getCommandStatus())
		{
			return true;	//OK
		}
		else
		{
			this->message = commandExecutor.getOutput();
			return false;
		}

		return true;
	}

	//lvremove -f /dev/SVM_1/vs1001
	bool removeLogicalPartition(std::string lv_name, std::string volume_group)
	{
		std::string command = "lvremove -f /dev/" + volume_group + "/" + lv_name;
		//std::cout << "RLP: [" << command << "]" << std::endl;

		//RUN COMMANDS
		commandExecutor.addCommand(command, 0);
		commandExecutor.runCommand();

		//CHECK IF COMMAND RAN OK
		if(commandExecutor.getCommandStatus())
		{
			return true;	//OK
		}
		else
		{
			this->message = commandExecutor.getOutput();
			return false;
		}

		return true;

		return 1;
	}

	//lvresize -L {SPACE}G /dev/SVM_1/vs1001
	bool resizeLogicalPartition(std::string new_space, std::string lv_name, std::string volume_group)
	{
		std::string command = "lvresize -L " + new_space + "G /dev/" + volume_group + "/" + lv_name;
		//std::cout << "RESIZE LP: [" << command << "]" << std::endl;

		//RUN COMMANDS
		commandExecutor.addCommand(command, 0);
		commandExecutor.runCommand();

		//CHECK IF COMMAND RAN OK
		if(commandExecutor.getCommandStatus())
		{
			return true;	//OK
		}
		else
		{
			this->message = commandExecutor.getOutput();
			return false;
		}

		return true;
	}



private:
	MiscTool miscTool;
	CommandExecutor commandExecutor;
	std::string message;
};



#endif
