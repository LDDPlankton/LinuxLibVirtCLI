#include "OSListDAO.h"

OSListDAO::OSListDAO(SQLite &db) : db(db)
{

}

OSListDAO::~OSListDAO()
{

}

int OSListDAO::insert(OSListModel model)
{
	string sql = "INSERT INTO `os_list` (`name`) VALUES (?);";
	this->db.setQuery(sql);
	this->db.setParamText(model.getName());
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("OSListDAO::insert() Error: " + this->db.getErrorMessage());
		return 0;
	}

	return this->db.getLastInsertID();
}
OSListModel OSListDAO::findByID(int id)
{
	OSListModel model;
	model.setID(id);
	return this->findBy(model).front();
}
list<OSListModel> OSListDAO::findBy(OSListModel model)
{
	list<OSListModel> umodel;
	string sql = "SELECT * FROM `os_list`";
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
				this->setErrorMessage("OSListDAO::findBy() Error: " + this->db.getErrorMessage());
				return umodel;
			}

			//IF FOUND SOME RESULTS
			if(this->db.getResultCount() > 0)
			{
				//GET RESULT _ POPULATE MODEL [ONLY ONE RESULT SO LOOP OK]
				vector< map<string,string> > result = this->db.fetchArray();
				for(vector< map<string,string> >::iterator i = result.begin(); i != result.end(); i++)
				{
					OSListModel tmpModel;
					tmpModel.setData(*i);
					umodel.push_back( tmpModel );
				}
			}
		}
		start++;
	}
	return umodel;
}
bool OSListDAO::deleteByID(int id)
{
	string sql = "DELETE FROM `os_list` WHERE `id`=?;";

	this->db.setQuery(sql);
	this->db.setParamInt(id);
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("OSList::deleteByID() Error: " + this->db.getErrorMessage());
		return false;
	}
	return true;
}
bool OSListDAO::deleteByModel(OSListModel model)
{
	string sql = "DELETE FROM `os_list` WHERE `id`=?;";

	this->db.setQuery(sql);
	this->db.setParamInt(model.getID());
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("OSList::deleteByModel() Error: " + this->db.getErrorMessage());
		return false;
	}
	return true;
}
bool OSListDAO::update(OSListModel model)
{
	string sql = "UPDATE `os_list` SET `name`=? WHERE `id`=?;";
	this->db.setQuery(sql);
	this->db.setParamText(model.getName());
	this->db.setParamInt(model.getID());
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("IPListDAO::update() Error: " + this->db.getErrorMessage());
		return false;
	}
	return true;
}
