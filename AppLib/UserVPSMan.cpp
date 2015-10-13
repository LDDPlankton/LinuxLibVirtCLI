#include "UserVPSMan.h"

UserVPSMan::UserVPSMan(SQLite &db) : uservpsDAO(db)
{


}

UserVPSMan::~UserVPSMan()
{

}

string UserVPSMan::getErrorMessage()
{
	return this->uservpsDAO.getErrorMessage();
}

int UserVPSMan::addVPS(int user_id, string hostname, int diskspace, int bandwidth, string name, int mem, int vcpu, int cpuunits, int cpupct)
{
	UserVPSModel umodel;

	umodel.setUserID(user_id);
	umodel.setVMHostName(hostname);
	umodel.setVMDiskSpace(diskspace);
	umodel.setVMBandwidth(bandwidth);
	umodel.setVMName(name);
	umodel.setVMMemory(mem);
	umodel.setVMVcpu(vcpu);
	umodel.setVMCpuUnits(cpuunits);
	umodel.setVMCpuPct(cpupct);
	umodel.setVMEnableVNC(0);

	int id = this->uservpsDAO.insert(umodel);
	return id;
}
bool UserVPSMan::deleteVPS(UserVPSModel model)
{
	return this->uservpsDAO.deleteByModel(model);
}
bool UserVPSMan::isVPSIDExist(int id)
{
	UserVPSModel result = this->uservpsDAO.findByID(id);
	if(result.getID() != 0)
		return true;
	else
		return false;
}
bool UserVPSMan::isVMNameExist(string name)
{
	UserVPSModel umodel;
	umodel.setVMName(name);
	UserVPSModel result = this->uservpsDAO.findBy(umodel).front();
	if(result.getID() != 0)
		return true;
	else
		return false;
}
UserVPSModel UserVPSMan::findByVPSID(int id)
{
	UserVPSModel result = this->uservpsDAO.findByID(id);
	return result;
}
UserVPSModel UserVPSMan::findByVMName(string name)
{
	UserVPSModel umodel;
	umodel.setVMName(name);
	UserVPSModel result = this->uservpsDAO.findBy(umodel).front();
	return result;
}
list<UserVPSModel> UserVPSMan::listVPSs()
{
	UserVPSModel model;
	list<UserVPSModel> listusers = this->findAllBy(model);
	return listusers;
}
list<UserVPSModel> UserVPSMan::findAllBy(UserVPSModel model)
{
	list<UserVPSModel> user_model_list = this->uservpsDAO.findBy(model);
	return user_model_list;
}
bool UserVPSMan::update(UserVPSModel model)
{
	return this->uservpsDAO.update(model);
}
