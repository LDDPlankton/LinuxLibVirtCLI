#include "UserVPSDAO.h"

UserVPSDAO::UserVPSDAO(SQLite &db) : db(db)
{

}

UserVPSDAO::~UserVPSDAO()
{

}

int UserVPSDAO::insert(UserVPSModel model)
{
	string sql = "INSERT INTO `user_vps` (`user_id`, `vm_os_id`, `vm_hostname`, `vm_diskspace`, `vm_bandwidth`, `vm_name`, `vm_memory`, `vm_vcpu`, `vm_cpuunits`, `vm_cpupct`, `vm_enable_vnc`)"
			"VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

	this->db.setQuery(sql);
	this->db.setParamInt(model.getUserID());
	this->db.setParamInt(model.getVMOSID());
	this->db.setParamText(model.getVMHostName());
	this->db.setParamInt(model.getVMDiskSpace());
	this->db.setParamInt(model.getVMBandwidth());
	this->db.setParamText(model.getVMName());
	this->db.setParamInt(model.getVMMemory());
	this->db.setParamInt(model.getVMVcpu());
	this->db.setParamInt(model.getVMCpuUnits());
	this->db.setParamInt(model.getVMCpuPct());
	this->db.setParamInt(model.getVMEnableVNC());
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("UserVPSDAO::insert() Error: " + this->db.getErrorMessage());
		return 0;
	}
	return this->db.getLastInsertID();
}
UserVPSModel UserVPSDAO::findByID(int id)
{
	UserVPSModel model;
	model.setID(id);
	return this->findBy(model).front();
}
list<UserVPSModel> UserVPSDAO::findBy(UserVPSModel model)
{
	list<UserVPSModel> umodel;
	string sql = "SELECT * FROM `user_vps`";
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
		if(model.getUserID() != 0)
		{
			if(start == 1)
				where += "`user_id`=? AND ";
			else
				this->db.setParamInt(model.getUserID());
		}
		if(model.getVMOSID() != 0)
		{
			if(start == 1)
				where += "`vm_os_id`=? AND ";
			else
				this->db.setParamInt(model.getVMOSID());
		}
		if(model.getVMHostName() != "")
		{
			if(start == 1)
				where += "`vm_hostname`=? AND ";
			else
				this->db.setParamText(model.getVMHostName());
		}
		if(model.getVMDiskSpace() != 0)
		{
			if(start == 1)
				where += "`vm_diskspace`=? AND ";
			else
				this->db.setParamInt(model.getVMDiskSpace());
		}
		if(model.getVMBandwidth() != 0)
		{
			if(start == 1)
				where += "`vm_bandwidth`=? AND ";
			else
				this->db.setParamInt(model.getVMBandwidth());
		}
		if(model.getVMName() != "")
		{
			if(start == 1)
				where += "`vm_name`=? AND ";
			else
				this->db.setParamText(model.getVMName());
		}
		if(model.getVMMemory() != 0)
		{
			if(start == 1)
				where += "`vm_memory`=? AND ";
			else
				this->db.setParamInt(model.getVMMemory());
		}
		if(model.getVMVcpu() != 0)
		{
			if(start == 1)
				where += "`vm_vcpu`=? AND ";
			else
				this->db.setParamInt(model.getVMVcpu());
		}
		if(model.getVMCpuUnits() != 0)
		{
			if(start == 1)
				where += "`vm_cpuunits`=? AND ";
			else
				this->db.setParamInt(model.getVMCpuUnits());
		}
		if(model.getVMCpuPct() != 0)
		{
			if(start == 1)
				where += "`vm_cpupct`=? AND ";
			else
				this->db.setParamInt(model.getVMCpuPct());
		}
		if(model.getVMEnableVNC() != 0)
		{
			if(start == 1)
				where += "`vm_enable_vnc`=? AND ";
			else
				this->db.setParamInt(model.getVMEnableVNC());
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
				this->setErrorMessage("UserVPSDAO::findBy() Error: " + this->db.getErrorMessage());
				return umodel;
			}

			//IF FOUND SOME RESULTS
			if(this->db.getResultCount() > 0)
			{
				//GET RESULT _ POPULATE MODEL [ONLY ONE RESULT SO LOOP OK]
				vector< map<string,string> > result = this->db.fetchArray();
				for(vector< map<string,string> >::iterator i = result.begin(); i != result.end(); i++)
				{
					UserVPSModel tmpModel;
					tmpModel.setData(*i);
					umodel.push_back( tmpModel );
				}
			}
		}
		start++;
	}
	return umodel;
}
bool UserVPSDAO::deleteByID(int id)
{
	string sql = "DELETE FROM `user_vps` WHERE `id`=?;";

	this->db.setQuery(sql);
	this->db.setParamInt(id);
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("UserVPSDAO::deleteByID() Error: " + this->db.getErrorMessage());
		return false;
	}
	return true;
}
bool UserVPSDAO::deleteByModel(UserVPSModel model)
{
	string sql = "DELETE FROM `user_vps` WHERE `id`=?;";

	this->db.setQuery(sql);
	this->db.setParamInt(model.getID());
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("UserVPSDAO::deleteByModel() Error: " + this->db.getErrorMessage());
		return false;
	}
	return true;
}
bool UserVPSDAO::update(UserVPSModel model)
{
	string sql = "UPDATE `user_vps` SET `user_id`=?, `vm_os_id`=?, `vm_hostname`=?, `vm_diskspace`=?, `vm_bandwidth`=?, `vm_name`=?, `vm_memory`=?, `vm_vcpu`=?, `vm_cpuunits`=?, `vm_cpupct`=?, `vm_enable_vnc`=? WHERE `id`=?;";
	this->db.setQuery(sql);
	this->db.setParamInt(model.getUserID());
	this->db.setParamInt(model.getVMOSID());
	this->db.setParamText(model.getVMHostName());
	this->db.setParamInt(model.getVMDiskSpace());
	this->db.setParamInt(model.getVMBandwidth());
	this->db.setParamText(model.getVMName());
	this->db.setParamInt(model.getVMMemory());
	this->db.setParamInt(model.getVMVcpu());
	this->db.setParamInt(model.getVMCpuUnits());
	this->db.setParamInt(model.getVMCpuPct());
	this->db.setParamInt(model.getVMEnableVNC());
	this->db.setParamInt(model.getID());
	this->db.runQuery();
	if( !this->db.getQueryStatus() )
	{
		this->setErrorMessage("UserVPSDAO::update() Error: " + this->db.getErrorMessage());
		return false;
	}
	return true;
}
