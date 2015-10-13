#include "KVMConfig.h"

KVMConfig::KVMConfig()
{

}

KVMConfig::~KVMConfig()
{

}

/*
 * This function will load from our templates, the various virtualization files so they can later be written to the install location
 *
 * @param string
 */
string KVMConfig::generateConfig()
{
	string filename = "Files/KVMBase.txt";
	string config = "";

	//OPEN FILE
	this->myfile.open(filename.c_str(), std::ios::in);
	if(!myfile)
	{
		cout << "Failed to load Config File: " << filename << endl;
		exit(1);
	}

	//LOOP + ADD LINE
	char line[1024];
	while( myfile.getline(line,1024) )
	{
		string tmp = string(line) + "\n";
		config += tmp;
	}
	this->myfile.close();

	//TRIM CONFIG
	this->strhelper.trim(config);

	return config;
}
