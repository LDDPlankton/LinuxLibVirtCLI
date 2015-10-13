#ifndef OSLISTMODEL_H_
#define OSLISTMODEL_H_

#include <iostream>
#include <map>
#include "Helpers/StringHelper.h"
using namespace std;

class OSListModel
{
public:
	OSListModel();
	~OSListModel();
	bool setData(map<string,string> newdata);
	map<string,string> getData();

	void setID(int s);
	void setName(string s);

	int getID();
	string getName();

private:
	map<string,string> data;
	StringHelper strhelper;

	int id;
	string name;
};

#endif
