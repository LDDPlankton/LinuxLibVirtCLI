#include "UserMan.h"

UserMan::UserMan(SQLite &db) : userDAO(db)
{

}

UserMan::~UserMan()
{

}

string UserMan::getErrorMessage()
{
	return this->userDAO.getErrorMessage();
}

int UserMan::addUser(string email, string password)
{
	Date myDate;
	UserModel umodel;

	umodel.setEmail(email);
	umodel.setPassword(password);
	umodel.setTimeCreated(myDate.generateDate());
	int user_id = this->userDAO.insert(umodel);
	return user_id;
}

bool UserMan::deleteUser(UserModel model)
{
	return this->userDAO.deleteByModel(model);
}

bool UserMan::isUserIDExist(int id)
{
	UserModel result = this->userDAO.findByID(id);
	if(result.getID() != 0)
		return true;
	else
		return false;
}
bool UserMan::isEmailExist(string email)
{
	UserModel umodel;
	umodel.setEmail(email);
	UserModel result = this->userDAO.findBy(umodel).front();
	if(result.getID() != 0)
		return true;
	else
		return false;
}
UserModel UserMan::findByUserID(int id)
{
	UserModel result = this->userDAO.findByID(id);
	return result;
}
UserModel UserMan::findByEmail(string email)
{
	UserModel umodel;
	umodel.setEmail(email);
	UserModel result = this->userDAO.findBy(umodel).front();
	return result;
}
list<UserModel> UserMan::listUsers()
{
	UserModel model;
	list<UserModel> listusers = this->findAllBy(model);
	return listusers;
}
list<UserModel> UserMan::findAllBy(UserModel model)
{
	list<UserModel> user_model_list = this->userDAO.findBy(model);
	return user_model_list;
}
