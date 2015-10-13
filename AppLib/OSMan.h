#ifndef OSMAN_H_
#define OSMAN_H_

#include <iostream>
#include <list>
#include "../AppModel/OSListModel.h"
#include "../AppDAO/OSListDAO.h"
using namespace std;

class OSMan
{
public:
	OSMan(SQLite &db);
	~OSMan();
	string getErrorMessage();

	int addOS(string name);
	bool deleteOS(OSListModel model);
	bool isOSIDExist(int id);
	bool isOSNameExist(string name);
	OSListModel findByOSID(int id);
	OSListModel findByOSName(string name);
	list<OSListModel> listOSs();
	list<OSListModel> findAllBy(OSListModel model);

private:
	OSListDAO oslistDAO;
};

#endif
