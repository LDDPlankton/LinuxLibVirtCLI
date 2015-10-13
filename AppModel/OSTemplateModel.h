#ifndef OSTEMPLATEMODEL_H_
#define OSTEMPLATEMODEL_H_

#include <iostream>
#include <map>
#include "Helpers/StringHelper.h"
using namespace std;

class OSTemplateModel
{
public:
	OSTemplateModel();
	~OSTemplateModel();
	bool setData(map<string,string> newdata);
	map<string,string> getData();

	void setID(int s);
	void setOSID(int s);
	void setName(string s);
	void setTemplatePath(string s);
	int getID();
	int getOSID();
	string getName();
	string getTemplatePath();

private:
	map<string,string> data;
	StringHelper strhelper;
	int id;
	int os_id;
	string name;
	string template_path;

};

#endif
