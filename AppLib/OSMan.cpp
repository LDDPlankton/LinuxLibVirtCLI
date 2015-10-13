#include "OSMan.h"

OSMan::OSMan(SQLite &db) : oslistDAO(db)
{

}

OSMan::~OSMan()
{

}

string OSMan::getErrorMessage()
{
	return this->oslistDAO.getErrorMessage();
}

int OSMan::addOS(string name)
{
	OSListModel umodel;
	umodel.setName(name);
	int id = this->oslistDAO.insert(umodel);
	return id;
}
bool OSMan::deleteOS(OSListModel model)
{
	return this->oslistDAO.deleteByModel(model);
}
bool OSMan::isOSIDExist(int id)
{
	OSListModel result = this->oslistDAO.findByID(id);
	if(result.getID() != 0)
		return true;
	else
		return false;
}
bool OSMan::isOSNameExist(string name)
{
	OSListModel umodel;
	umodel.setName(name);
	OSListModel result = this->oslistDAO.findBy(umodel).front();
	if(result.getID() != 0)
		return true;
	else
		return false;
}
OSListModel OSMan::findByOSID(int id)
{
	OSListModel result = this->oslistDAO.findByID(id);
	return result;
}
OSListModel OSMan::findByOSName(string name)
{
	OSListModel umodel;
	umodel.setName(name);
	OSListModel result = this->oslistDAO.findBy(umodel).front();
	return result;
}
list<OSListModel> OSMan::listOSs()
{
	OSListModel model;
	list<OSListModel> listusers = this->findAllBy(model);
	return listusers;
}
list<OSListModel> OSMan::findAllBy(OSListModel model)
{
	list<OSListModel> list = this->oslistDAO.findBy(model);
	return list;
}
