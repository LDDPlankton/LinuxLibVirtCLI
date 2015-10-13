#ifndef USERMAN_H_
#define USERMAN_H_

#include <iostream>
#include <list>
#include "../AppModel/UserModel.h"
#include "../AppDAO/UserDAO.h"
#include "SUtil/Date.h"
using namespace std;

class UserMan
{
public:
	UserMan(SQLite &db);
	~UserMan();
	string getErrorMessage();
	int addUser(string email, string password);
	bool deleteUser(UserModel model);
	bool isUserIDExist(int id);
	bool isEmailExist(string email);
	UserModel findByUserID(int id);
	UserModel findByEmail(string email);
	list<UserModel> listUsers();
	list<UserModel> findAllBy(UserModel model);

private:
	UserDAO userDAO;
};

#endif
