#ifndef USERVPSMAN_H_
#define USERVPSMAN_H_

#include <iostream>
#include <list>
#include "../AppModel/UserVPSModel.h"
#include "../AppDAO/UserVPSDAO.h"
using namespace std;

class UserVPSMan
{
public:
	UserVPSMan(SQLite &db);
	~UserVPSMan();
	string getErrorMessage();

	int addVPS(int user_id, string hostname, int diskspace, int bandwidth, string name, int mem, int vcpu, int cpuunits, int cpupct);
	bool deleteVPS(UserVPSModel model);
	bool isVPSIDExist(int id);
	bool isVMNameExist(string name);
	UserVPSModel findByVPSID(int id);
	UserVPSModel findByVMName(string name);
	list<UserVPSModel> listVPSs();
	list<UserVPSModel> findAllBy(UserVPSModel model);
	bool update(UserVPSModel model);

private:
	UserVPSDAO uservpsDAO;
};

#endif
