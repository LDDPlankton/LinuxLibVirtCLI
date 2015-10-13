#ifndef OSTEMPLATEMAN_H_
#define OSTEMPLATEMAN_H_

#include <iostream>
#include <list>
#include "../AppModel/OSTemplateModel.h"
#include "../AppDAO/OSTemplateDAO.h"
using namespace std;

class OSTemplateMan
{
public:
	OSTemplateMan(SQLite &db);
	~OSTemplateMan();
	string getErrorMessage();

	int addOSTemplate(int os_id, string name, string template_path);
	bool deleteOSTemplate(OSTemplateModel model);
	bool isTemplateIDExist(int id);
	bool isTemplateNameExist(string name);
	OSTemplateModel findByTemplateID(int id);
	OSTemplateModel findByTemplateName(string name);
	list<OSTemplateModel> listTemplates();
	list<OSTemplateModel> findAllBy(OSTemplateModel model);

private:
	OSTemplateDAO ostplDAO;
};

#endif
