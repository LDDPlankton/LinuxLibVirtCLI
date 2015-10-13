#include "ConfigSettingModel.h"

ConfigSettingModel::ConfigSettingModel()
{
	this->id = 0;
	this->key = "";
	this->value = "";
}

ConfigSettingModel::~ConfigSettingModel()
{

}

bool ConfigSettingModel::setData(map<string,string> newdata)
{
	this->id = this->strhelper.toInt( newdata["id"] );
	this->key = newdata["key"];
	this->value = newdata["value"];
	return true;
}

map<string,string> ConfigSettingModel::getData()
{
	return this->data;
}

void ConfigSettingModel::setID(int s) { this->id = s; }
void ConfigSettingModel::setKey(string s) { this->key = s; }
void ConfigSettingModel::setValue(string s) { this->value = s; }
int ConfigSettingModel::getID() { return this->id; }
string ConfigSettingModel::getKey() { return this->key; }
string ConfigSettingModel::getValue() { return this->value; }
