#include "OSTemplateModel.h"

OSTemplateModel::OSTemplateModel()
{
	this->id = 0;
	this->os_id = 0;
	this->name = "";
	this->template_path = "";
}

OSTemplateModel::~OSTemplateModel()
{

}

bool OSTemplateModel::setData(map<string,string> newdata)
{
	this->id = this->strhelper.toInt( newdata["id"] );
	this->os_id = this->strhelper.toInt( newdata["os_id"] );
	this->name = newdata["name"];
	this->template_path = newdata["template_path"];
	return true;
}

map<string,string> OSTemplateModel::getData()
{
	return this->data;
}

void OSTemplateModel::setID(int s) { this->id = s; }
void OSTemplateModel::setOSID(int s) { this->os_id = s; }
void OSTemplateModel::setName(string s) { this->name = s; }
void OSTemplateModel::setTemplatePath(string s) { this->template_path = s; }
int OSTemplateModel::getID() { return this->id; }
int OSTemplateModel::getOSID() { return this->os_id; }
string OSTemplateModel::getName() { return this->name; }
string OSTemplateModel::getTemplatePath() { return this->template_path; }


