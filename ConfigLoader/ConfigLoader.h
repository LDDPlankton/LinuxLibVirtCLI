#ifndef CONFIGLOADER_H_
#define CONFIGLOADER_H_

#include <fstream>
#include "ConfigSettings.h"

/*
 * CONFIG USAGE:
 * setVariable("name", "VALUE!");
 * setBlock("VNC_BLOCK", "BLOCK_HERE!");
 */

class ConfigLoader
{
public:
	ConfigLoader()
	{
		this->filename = "";
	}
	~ConfigLoader()
	{

	}

	/*
	 * This function will load a KVM config file to be used/modified for any new VM
	 *
	 * @param string type [VZ type]
	 * @return boolean
	 */
	bool loadConfig(std::string type)
	{
		if(type == "KVM")
		{
			this->filename = "/usr/local/libvirtvm/config/virt_kvm_config.txt";
		}
		else
			return false;	//FAILED

		return this->doConfigLoad();
	}

	/*
	 * This function sets a variable to be replaced in the Virtualization base config
	 *
	 * @param string key
	 * @param string value
	 * @return void
	 */
	void setVariable(std::string key, std::string value)
	{
		this->config_settings.setVariable(key, value);
	}

	/*
	 * This function will set a block of code to be added into the Virtualization base config
	 *
	 * @param string block_name
	 * @param string block_value
	 * @return void
	 */
	void setBlock(std::string block_name, std::string block_value)
	{
		this->config_settings.setBlock(block_name, block_value);
	}

	void print()
	{
		this->config_settings.print();
	}

	std::string getXMLConfig()
	{
		return this->config_settings.getXMLConfig();
	}


private:

	/*
	 * This function will handle the actual file loading into a tmp buffer
	 *
	 * @return boolean
	 */
	bool doConfigLoad()
	{
		this->myfile.open(this->filename.c_str(), std::ios::in);

		if(!myfile)
		{
			std::cout << "Failed to load Config File: " << this->filename << std::endl;
			return false;
		}

		//LOOP + ADD LINE
		char line[1024];
		while( myfile.getline(line,1024) )
		{
			std::string tmp = std::string(line);
			this->config_settings.addLine(tmp);
		}
		this->myfile.close();

		return true;
	}

	std::ifstream myfile;
	std::string filename;
	std::string load_buf;
	ConfigSettings config_settings;
};

#endif
