#ifndef IPMAN_H_
#define IPMAN_H_

#include <iostream>
#include <list>
#include "../AppModel/IPListModel.h"
#include "../AppDAO/IPListDAO.h"
using namespace std;

class IPMan
{
public:
	IPMan(SQLite &db);
	~IPMan();
	string getErrorMessage();

	int addIP(string ip_type, string ip);
	bool deleteIP(IPListModel model);
	bool isIPIDExist(int id);
	bool isIPExist(string ip);
	IPListModel findByID(int id);
	IPListModel findByIP(string ip);
	list<IPListModel> listIPs();
	list<IPListModel> findAllBy(IPListModel model);
	bool update(IPListModel model);

private:
	IPListDAO iplistDAO;
};

#endif
