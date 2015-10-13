#include "IPListModel.h"

IPListModel::IPListModel()
{
	this->id = 0;
	this->vps_id = 0;
	this->ip_type = "";
	this->ip = "";

}

IPListModel::~IPListModel()
{

}

bool IPListModel::setData(map<string,string> newdata)
{
	this->id = this->strhelper.toInt( newdata["id"] );
	this->vps_id = this->strhelper.toInt( newdata["vps_id"] );
	this->ip_type = newdata["ip_type"];
	this->ip = newdata["ip"];
	return true;
}

map<string,string> IPListModel::getData()
{
	return this->data;
}

void IPListModel::setID(int s) { this->id = s; }
void IPListModel::setVPSID(int s) { this->vps_id = s; }
void IPListModel::setIPType(string s) { this->ip_type = s; }
void IPListModel::setIP(string s) { this->ip = s; }

int IPListModel::getID() { return this->id; }
int IPListModel::getVPSID() { return this->vps_id; }
string IPListModel::getIPType() { return this->ip_type; }
string IPListModel::getIP() { return this->ip; }
