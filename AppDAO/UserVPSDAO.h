#ifndef USERVPSDAO_H_
#define USERVPSDAO_H_

#include <iostream>
#include <list>
#include "../AppDAO/DAOBase.h"
#include "../AppModel/UserVPSModel.h"
#include "SQLite/SQLite.h"
using namespace std;

class UserVPSDAO : public DAOBase
{
public:
	UserVPSDAO(SQLite &db);
	~UserVPSDAO();
	int insert(UserVPSModel model);
	UserVPSModel findByID(int id);
	list<UserVPSModel> findBy(UserVPSModel model);
	bool deleteByID(int id);
	bool deleteByModel(UserVPSModel model);
	bool update(UserVPSModel model);

private:
	SQLite &db;
};

#endif
