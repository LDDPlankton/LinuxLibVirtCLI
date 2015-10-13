#ifndef KVMCONFIG_H_
#define KVMCONFIG_H_

#include <iostream>
#include <cstdlib>
#include <fstream>
#include "Helpers/StringHelper.h"
using namespace std;

class KVMConfig
{
public:
	KVMConfig();
	~KVMConfig();
	string generateConfig();

private:
	ifstream myfile;
	StringHelper strhelper;
};

#endif
