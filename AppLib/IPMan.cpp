#include "IPMan.h"

IPMan::IPMan(SQLite &db) : iplistDAO(db)
{

}

IPMan::~IPMan()
{

}

string IPMan::getErrorMessage()
{
	return this->iplistDAO.getErrorMessage();
}

int IPMan::addIP(string ip_type, string ip)
{
	IPListModel umodel;
	umodel.setIPType(ip_type);
	umodel.setIP(ip);
	int id = this->iplistDAO.insert(umodel);
	return id;
}
bool IPMan::deleteIP(IPListModel model)
{
	return this->iplistDAO.deleteByModel(model);
}
bool IPMan::isIPIDExist(int id)
{
	IPListModel result = this->iplistDAO.findByID(id);
	if(result.getID() != 0)
		return true;
	else
		return false;
}
bool IPMan::isIPExist(string ip)
{
	IPListModel umodel;
	umodel.setIP(ip);
	IPListModel result = this->iplistDAO.findBy(umodel).front();
	if(result.getID() != 0)
		return true;
	else
		return false;
}
IPListModel IPMan::findByID(int id)
{
	IPListModel result = this->iplistDAO.findByID(id);
	return result;
}
IPListModel IPMan::findByIP(string ip)
{
	IPListModel umodel;
	umodel.setIP(ip);
	IPListModel result = this->iplistDAO.findBy(umodel).front();
	return result;
}
list<IPListModel> IPMan::listIPs()
{
	IPListModel model;
	list<IPListModel> listusers = this->findAllBy(model);
	return listusers;
}
list<IPListModel> IPMan::findAllBy(IPListModel model)
{
	list<IPListModel> list = this->iplistDAO.findBy(model);
	return list;
}
bool IPMan::update(IPListModel model)
{
	return this->iplistDAO.update(model);
}
