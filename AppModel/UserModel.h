#ifndef USERMODEL_H_
#define USERMODEL_H_

#include <iostream>
#include <map>
#include "Helpers/StringHelper.h"
using namespace std;

class UserModel
{
public:
	UserModel();
	~UserModel();
	bool setData(map<string,string> newdata);
	map<string,string> getData();

	void setID(int s);
	void setEmail(string s);
	void setPassword(string s);
	void setTimeCreated(string s);
	int getID();
	string getEmail();
	string getPassword();
	string getTimeCreated();

private:
	map<string,string> data;
	StringHelper strhelper;
	int id;
	string email;
	string password;
	string time_created;

};

#endif
