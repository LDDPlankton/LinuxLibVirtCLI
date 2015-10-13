#ifndef CONFIGSETTINGDAO_H_
#define CONFIGSETTINGDAO_H_

#include <iostream>
#include <list>
#include "../AppDAO/DAOBase.h"
#include "../AppModel/ConfigSettingModel.h"
#include "SQLite/SQLite.h"
using namespace std;

class ConfigSettingDAO : public DAOBase
{
public:
	ConfigSettingDAO(SQLite &db);
	~ConfigSettingDAO();
	int insert(ConfigSettingModel model);
	ConfigSettingModel findByID(int id);
	list<ConfigSettingModel> findBy(ConfigSettingModel model);
	bool deleteByID(int id);
	bool deleteByModel(ConfigSettingModel model);
	bool update(ConfigSettingModel model);

private:
	SQLite &db;
};

#endif
