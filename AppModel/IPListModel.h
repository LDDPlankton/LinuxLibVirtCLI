#ifndef IPLISTMODEL_H_
#define IPLISTMODEL_H_

#include <iostream>
#include <map>
#include "Helpers/StringHelper.h"
using namespace std;

class IPListModel
{
public:
	IPListModel();
	~IPListModel();
	bool setData(map<string,string> newdata);
	map<string,string> getData();

	void setID(int s);
	void setVPSID(int s);
	void setIPType(string s);
	void setIP(string s);

	int getID();
	int getVPSID();
	string getIPType();
	string getIP();

private:
	map<string,string> data;
	StringHelper strhelper;
	int id;
	int vps_id;
	string ip_type;
	string ip;
};

#endif
