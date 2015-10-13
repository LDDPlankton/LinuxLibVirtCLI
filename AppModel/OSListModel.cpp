#include "OSListModel.h"

OSListModel::OSListModel()
{
	this->id = 0;
	this->name = "";
}

OSListModel::~OSListModel()
{

}

bool OSListModel::setData(map<string,string> newdata)
{
	this->id = this->strhelper.toInt( newdata["id"] );
	this->name = newdata["name"];
	return true;
}

map<string,string> OSListModel::getData()
{
	return this->data;
}

void OSListModel::setID(int s) { this->id = s; }
void OSListModel::setName(string s) { this->name = s; }

int OSListModel::getID() { return this->id; }
string OSListModel::getName() { return this->name; }
