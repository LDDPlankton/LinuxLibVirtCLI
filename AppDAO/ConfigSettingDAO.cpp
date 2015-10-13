#include "ConfigSettingDAO.h"

ConfigSettingDAO::ConfigSettingDAO(SQLite &db) : db(db)
{

}

ConfigSettingDAO::~ConfigSettingDAO()
{

}

int ConfigSettingDAO::insert(ConfigSettingModel model)
{
	string sql = "INSERT INTO `config_settings` (`key`, `value`) VALUES (?, ?);";
	this->db.setQuery(sql);
	this->db.setParamText(model.getKey());
	this->db.setParamText(model.getValue());
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("ConfigSettingDAO::insert() Error: " + this->db.getErrorMessage());
		return 0;
	}

	return this->db.getLastInsertID();
}
ConfigSettingModel ConfigSettingDAO::findByID(int id)
{
	ConfigSettingModel model;
	model.setID(id);
	return this->findBy(model).front();
}
list<ConfigSettingModel> ConfigSettingDAO::findBy(ConfigSettingModel model)
{
	list<ConfigSettingModel> umodel;
	string sql = "SELECT * FROM `config_settings`";
	string where = "";
	int start = 1;

	//LOOP
	while(start <= 2)
	{
		if(model.getID() != 0)
		{
			if(start == 1)
				where += "`id`=? AND ";
			else
				this->db.setParamInt(model.getID());
		}
		if(model.getKey() != "")
		{
			if(start == 1)
				where += "`key`=? AND ";
			else
				this->db.setParamText(model.getKey());
		}
		if(model.getValue() != "")
		{
			if(start == 1)
				where += "`value`=? AND ";
			else
				this->db.setParamText(model.getValue());
		}

		//FIX SQL STRING + RUN QUERY
		if(start == 1)
		{
			//FIND LAST INSTANCE OF AND + IF EXIST REMOVE IT
			string::size_type st = where.find_last_of("AND");
			if(st != string::npos)
				where = where.substr(0, where.length()-5);
			strhelper.trim(where);

			if(where.length() > 0)
				sql += " WHERE " + where + " LIMIT 1;";

			//SET QUERY
			this->db.setQuery(sql);
		}
		else
		{
			//RUN QUERY
			this->db.runQuery();
			if( !this->db.getQueryStatus() )
			{
				this->setErrorMessage("ConfigSettingDAO::findBy() Error: " + this->db.getErrorMessage());
				return umodel;
			}

			//IF FOUND SOME RESULTS
			if(this->db.getResultCount() > 0)
			{
				//GET RESULT _ POPULATE MODEL [ONLY ONE RESULT SO LOOP OK]
				vector< map<string,string> > result = this->db.fetchArray();
				for(vector< map<string,string> >::iterator i = result.begin(); i != result.end(); i++)
				{
					ConfigSettingModel tmpModel;
					tmpModel.setData(*i);
					umodel.push_back( tmpModel );
				}
			}
		}
		start++;
	}
	return umodel;
}
bool ConfigSettingDAO::deleteByID(int id)
{
	string sql = "DELETE FROM `config_settings` WHERE `id`=?;";

	this->db.setQuery(sql);
	this->db.setParamInt(id);
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("ConfigSettingDAO::deleteByID() Error: " + this->db.getErrorMessage());
		return false;
	}
	return true;
}
bool ConfigSettingDAO::deleteByModel(ConfigSettingModel model)
{
	string sql = "DELETE FROM `config_settings` WHERE `id`=?;";

	this->db.setQuery(sql);
	this->db.setParamInt(model.getID());
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("ConfigSettingDAO::deleteByModel() Error: " + this->db.getErrorMessage());
		return false;
	}
	return true;
}
bool ConfigSettingDAO::update(ConfigSettingModel model)
{
	string sql = "UPDATE `config_settings` SET `key`=?, `value`=? WHERE `id`=?;";
	this->db.setQuery(sql);
	this->db.setParamText(model.getKey());
	this->db.setParamText(model.getValue());
	this->db.setParamInt(model.getID());
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("ConfigSettingDAO::update() Error: " + this->db.getErrorMessage());
		return false;
	}
	return true;
}
