#include "IPListDAO.h"

IPListDAO::IPListDAO(SQLite &db) : db(db)
{

}

IPListDAO::~IPListDAO()
{

}

int IPListDAO::insert(IPListModel model)
{
	string sql = "INSERT INTO `ip_list` (`vps_id`,`ip_type`,`ip`) VALUES (?, ?, ?);";
	this->db.setQuery(sql);
	this->db.setParamInt(model.getVPSID());
	this->db.setParamText(model.getIPType());
	this->db.setParamText(model.getIP());
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("UserDAO::insert() Error: " + this->db.getErrorMessage());
		return 0;
	}

	return this->db.getLastInsertID();
}
IPListModel IPListDAO::findByID(int id)
{
	IPListModel model;
	model.setID(id);
	return this->findBy(model).front();
}
list<IPListModel> IPListDAO::findBy(IPListModel model)
{
	list<IPListModel> umodel;
	string sql = "SELECT * FROM `ip_list`";
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
		if(model.getVPSID() != 0)
		{
			if(start == 1)
				where += "`vps_id`=? AND ";
			else
				this->db.setParamInt(model.getVPSID());
		}
		if(model.getIPType() != "")
		{
			if(start == 1)
				where += "`ip_type`=? AND ";
			else
				this->db.setParamText(model.getIPType());
		}
		if(model.getIP() != "")
		{
			if(start == 1)
				where += "`ip`=? AND ";
			else
				this->db.setParamText(model.getIP());
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
				this->setErrorMessage("IPListDAO::findBy() Error: " + this->db.getErrorMessage());
				return umodel;
			}

			//IF FOUND SOME RESULTS
			if(this->db.getResultCount() > 0)
			{
				//GET RESULT _ POPULATE MODEL [ONLY ONE RESULT SO LOOP OK]
				vector< map<string,string> > result = this->db.fetchArray();
				for(vector< map<string,string> >::iterator i = result.begin(); i != result.end(); i++)
				{
					IPListModel tmpModel;
					tmpModel.setData(*i);
					umodel.push_back( tmpModel );
				}
			}
		}
		start++;
	}
	return umodel;
}
bool IPListDAO::deleteByID(int id)
{
	string sql = "DELETE FROM `ip_list` WHERE `id`=?;";

	this->db.setQuery(sql);
	this->db.setParamInt(id);
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("IPList::deleteByID() Error: " + this->db.getErrorMessage());
		return false;
	}
	return true;
}
bool IPListDAO::deleteByModel(IPListModel model)
{
	string sql = "DELETE FROM `ip_list` WHERE `id`=?;";

	this->db.setQuery(sql);
	this->db.setParamInt(model.getID());
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("IPList::deleteByModel() Error: " + this->db.getErrorMessage());
		return false;
	}
	return true;
}
bool IPListDAO::update(IPListModel model)
{
	string sql = "UPDATE `ip_list` SET `vps_id`=?, `ip_type`=?, `ip`=? WHERE `id`=?;";
	this->db.setQuery(sql);
	this->db.setParamInt(model.getVPSID());
	this->db.setParamText(model.getIPType());
	this->db.setParamText(model.getIP());
	this->db.setParamInt(model.getID());
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("IPListDAO::update() Error: " + this->db.getErrorMessage());
		return false;
	}
	return true;
}
