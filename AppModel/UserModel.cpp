#include "UserModel.h"

UserModel::UserModel()
{
	this->id = 0;
	this->email = "";
	this->password = "";
	this->time_created = "";
}

UserModel::~UserModel()
{

}

bool UserModel::setData(map<string,string> newdata)
{
	this->id = this->strhelper.toInt( newdata["id"] );
	this->email = newdata["email"];
	this->password = newdata["password"];
	this->time_created = newdata["time_created"];
	return true;
}

map<string,string> UserModel::getData()
{
	return this->data;
}

void UserModel::setID(int s) { this->id = s; }
void UserModel::setEmail(string s) { this->email = s; }
void UserModel::setPassword(string s) { this->password = s; }
void UserModel::setTimeCreated(string s) { this->time_created = s; }
int UserModel::getID() { return this->id; }
string UserModel::getEmail() { return this->email; }
string UserModel::getPassword() { return this->password; }
string UserModel::getTimeCreated() { return this->time_created; }
