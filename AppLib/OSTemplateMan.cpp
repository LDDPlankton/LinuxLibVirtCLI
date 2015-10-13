#include "OSTemplateMan.h"

OSTemplateMan::OSTemplateMan(SQLite &db) : ostplDAO(db)
{

}

OSTemplateMan::~OSTemplateMan()
{

}

string OSTemplateMan::getErrorMessage()
{
	return this->ostplDAO.getErrorMessage();
}

int OSTemplateMan::addOSTemplate(int os_id, string name, string template_path)
{
	OSTemplateModel umodel;

	umodel.setName(name);
	umodel.setTemplatePath(template_path);
	umodel.setOSID(os_id);
	int id = this->ostplDAO.insert(umodel);
	return id;
}
bool OSTemplateMan::deleteOSTemplate(OSTemplateModel model)
{
	return this->ostplDAO.deleteByModel(model);
}
bool OSTemplateMan::isTemplateIDExist(int id)
{
	OSTemplateModel result = this->ostplDAO.findByID(id);
	if(result.getID() != 0)
		return true;
	else
		return false;
}
bool OSTemplateMan::isTemplateNameExist(string name)
{
	OSTemplateModel umodel;
	umodel.setName(name);
	OSTemplateModel result = this->ostplDAO.findBy(umodel).front();
	if(result.getID() != 0)
		return true;
	else
		return false;
}
OSTemplateModel OSTemplateMan::findByTemplateID(int id)
{
	OSTemplateModel result = this->ostplDAO.findByID(id);
	return result;
}
OSTemplateModel OSTemplateMan::findByTemplateName(string name)
{
	OSTemplateModel umodel;
	umodel.setName(name);
	OSTemplateModel result = this->ostplDAO.findBy(umodel).front();
	return result;
}
list<OSTemplateModel> OSTemplateMan::listTemplates()
{
	OSTemplateModel model;
	list<OSTemplateModel> listusers = this->findAllBy(model);
	return listusers;
}
list<OSTemplateModel> OSTemplateMan::findAllBy(OSTemplateModel model)
{
	list<OSTemplateModel> user_model_list = this->ostplDAO.findBy(model);
	return user_model_list;
}
