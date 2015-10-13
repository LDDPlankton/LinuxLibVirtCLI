#ifndef CONFIGSETTINGMODEL_H_
#define CONFIGSETTINGMODEL_H_

#include <iostream>
#include <map>
#include "Helpers/StringHelper.h"
using namespace std;

class ConfigSettingModel
{
public:
	ConfigSettingModel();
	~ConfigSettingModel();
	bool setData(map<string,string> newdata);
	map<string,string> getData();

	void setID(int s);
	void setKey(string s);
	void setValue(string s);
	int getID();
	string getKey();
	string getValue();

private:
	map<string,string> data;
	StringHelper strhelper;
	int id;
	string key;
	string value;
};

#endif
