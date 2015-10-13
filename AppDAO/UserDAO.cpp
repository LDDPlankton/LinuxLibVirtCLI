#include "UserDAO.h"

UserDAO::UserDAO(SQLite &db) : db(db)
{

}

UserDAO::~UserDAO()
{

}

int UserDAO::insert(UserModel model)
{
	string sql = "INSERT INTO `users` (`email`, `password`, `time_created`) VALUES (?, ?, ?);";
	this->db.setQuery(sql);
	this->db.setParamText(model.getEmail());
	this->db.setParamText(model.getPassword());
	this->db.setParamText(model.getTimeCreated());
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("UserDAO::insert() Error: " + this->db.getErrorMessage());
		return 0;
	}

	return this->db.getLastInsertID();
}
UserModel UserDAO::findByID(int id)
{
	UserModel model;
	model.setID(id);
	return this->findBy(model).front();
}
list<UserModel> UserDAO::findBy(UserModel model)
{
	list<UserModel> umodel;
	string sql = "SELECT * FROM `users`";
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
		if(model.getEmail() != "")
		{
			if(start == 1)
				where += "`email`=? AND ";
			else
				this->db.setParamText(model.getEmail());
		}
		if(model.getPassword() != "")
		{
			if(start == 1)
				where += "`password`=? AND ";
			else
				this->db.setParamText(model.getPassword());
		}
		if(model.getTimeCreated() != "")
		{
			if(start == 1)
				where += "`time_created`=? AND ";
			else
				this->db.setParamText(model.getTimeCreated());
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
				this->setErrorMessage("UserDAO::findBy() Error: " + this->db.getErrorMessage());
				return umodel;
			}

			//IF FOUND SOME RESULTS
			if(this->db.getResultCount() > 0)
			{
				//GET RESULT _ POPULATE MODEL [ONLY ONE RESULT SO LOOP OK]
				vector< map<string,string> > result = this->db.fetchArray();
				for(vector< map<string,string> >::iterator i = result.begin(); i != result.end(); i++)
				{
					UserModel tmpModel;
					tmpModel.setData(*i);
					umodel.push_back( tmpModel );
				}
			}
		}
		start++;
	}
	return umodel;
}
bool UserDAO::deleteByID(int id)
{
	string sql = "DELETE FROM `users` WHERE `id`=?;";

	this->db.setQuery(sql);
	this->db.setParamInt(id);
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("UserDAO::deleteByID() Error: " + this->db.getErrorMessage());
		return false;
	}
	return true;
}
bool UserDAO::deleteByModel(UserModel model)
{
	string sql = "DELETE FROM `users` WHERE `id`=?;";

	this->db.setQuery(sql);
	this->db.setParamInt(model.getID());
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("UserDAO::deleteByModel() Error: " + this->db.getErrorMessage());
		return false;
	}
	return true;
}
bool UserDAO::update(UserModel model)
{
	string sql = "UPDATE `users` SET `email`=?, `password`=?, `time_created`=? WHERE `id`=?;";
	this->db.setQuery(sql);
	this->db.setParamText(model.getEmail());
	this->db.setParamText(model.getPassword());
	this->db.setParamText(model.getTimeCreated());
	this->db.setParamInt(model.getID());
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("UserDAO::update() Error: " + this->db.getErrorMessage());
		return false;
	}
	return true;
}
