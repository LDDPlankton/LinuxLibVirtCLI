#include "OSTemplateDAO.h"

OSTemplateDAO::OSTemplateDAO(SQLite &db) : db(db)
{

}

OSTemplateDAO::~OSTemplateDAO()
{

}

int OSTemplateDAO::insert(OSTemplateModel model)
{
	string sql = "INSERT INTO `os_templates` (`os_id`, `name`, `template_path`) VALUES (?, ?, ?);";
	this->db.setQuery(sql);
	this->db.setParamInt(model.getOSID());
	this->db.setParamText(model.getName());
	this->db.setParamText(model.getTemplatePath());
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("OSTemplateDAO::insert() Error: " + this->db.getErrorMessage());
		return 0;
	}

	return this->db.getLastInsertID();
}
OSTemplateModel OSTemplateDAO::findByID(int id)
{
	OSTemplateModel model;
	model.setID(id);
	return this->findBy(model).front();
}
list<OSTemplateModel> OSTemplateDAO::findBy(OSTemplateModel model)
{
	list<OSTemplateModel> umodel;
	string sql = "SELECT * FROM `os_templates`";
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
		if(model.getName() != "")
		{
			if(start == 1)
				where += "`name`=? AND ";
			else
				this->db.setParamText(model.getName());
		}
		if(model.getTemplatePath() != "")
		{
			if(start == 1)
				where += "`template_path`=? AND ";
			else
				this->db.setParamText(model.getTemplatePath());
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
				this->setErrorMessage("OSTemplateDAO::findBy() Error: " + this->db.getErrorMessage());
				return umodel;
			}

			//IF FOUND SOME RESULTS
			if(this->db.getResultCount() > 0)
			{
				//GET RESULT _ POPULATE MODEL [ONLY ONE RESULT SO LOOP OK]
				vector< map<string,string> > result = this->db.fetchArray();
				for(vector< map<string,string> >::iterator i = result.begin(); i != result.end(); i++)
				{
					OSTemplateModel tmpModel;
					tmpModel.setData(*i);
					umodel.push_back( tmpModel );
				}
			}
		}
		start++;
	}
	return umodel;
}
bool OSTemplateDAO::deleteByID(int id)
{
	string sql = "DELETE FROM `os_templates` WHERE `id`=?;";

	this->db.setQuery(sql);
	this->db.setParamInt(id);
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("OSTemplateDAO::deleteByID() Error: " + this->db.getErrorMessage());
		return false;
	}
	return true;
}
bool OSTemplateDAO::deleteByModel(OSTemplateModel model)
{
	string sql = "DELETE FROM `os_templates` WHERE `id`=?;";

	this->db.setQuery(sql);
	this->db.setParamInt(model.getID());
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("OSTemplateDAO::deleteByModel() Error: " + this->db.getErrorMessage());
		return false;
	}
	return true;
}
bool OSTemplateDAO::update(OSTemplateModel model)
{
	string sql = "UPDATE `os_templates` SET `os_id`=?, `name`=?, `template_path`=? WHERE `id`=?;";
	this->db.setQuery(sql);
	this->db.setParamInt(model.getOSID());
	this->db.setParamText(model.getName());
	this->db.setParamText(model.getTemplatePath());
	this->db.setParamInt(model.getID());
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("OSTemplateDAO::update() Error: " + this->db.getErrorMessage());
		return false;
	}
	return true;
}

