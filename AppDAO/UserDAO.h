#ifndef USERDAO_H_
#define USERDAO_H_

#include <iostream>
#include <list>
#include "../AppDAO/DAOBase.h"
#include "../AppModel/UserModel.h"
#include "SQLite/SQLite.h"
using namespace std;

class UserDAO : public DAOBase
{
public:
	UserDAO(SQLite &db);
	~UserDAO();
	int insert(UserModel model);
	UserModel findByID(int id);
	list<UserModel> findBy(UserModel model);
	bool deleteByID(int id);
	bool deleteByModel(UserModel model);
	bool update(UserModel model);

private:
	SQLite &db;

};

#endif
