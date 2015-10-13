#ifndef CONFIGSETTINGS_H_
#define CONFIGSETTINGS_H_

#include <list>
#include <map>
#include <sstream>

class ConfigSettings
{
public:
	ConfigSettings()
	{

	}

	bool addLine(std::string newline)
	{
		this->mylist.push_back(newline);
		return true;
	}

	/*
	 * This function is the backend code to actually search for a variable string and replace it with a particular value
	 *
	 * @param string key
	 * @param string value
	 * @return int
	 */
	int setVariable(std::string key, std::string value)
	{
		std::string tmp;
		for(std::list<std::string>::iterator i = this->mylist.begin(); i!=this->mylist.end(); i++)
		{
			tmp = (*i);
			std::string tmp2 = "";
			std::string search = std::string("{") + key + std::string("}");

			int find_open = tmp.find(search);
			if(find_open != -1)
			{
				//std::cout << "FOUND=" << key << " V=" << value << std::endl;
				int find_start = tmp.find("{");
				int find_end = tmp.find("}");
				//tmp.replace(find_start, value.length(), value);	//2={,} + 1 to move past
				tmp2 = tmp.substr(0,find_start) + value + tmp.substr(find_end+1);
				(*i) = tmp2;
				//std::cout << "X=" << find_start << " Y=" << find_end << " Z=" << value.length() << " NEW:" << tmp << std::endl;
			}
		}
		return 0;
	}

	/*
	 * This function is the backend that takes care of searching and adding a block of code to our config
	 *
	 * @param string block_name
	 * @param string block_value
	 * @return int
	 */
	int setBlock(std::string block_name, std::string block_value)
	{
		std::string tmp;
		for(std::list<std::string>::iterator i = this->mylist.begin(); i!=this->mylist.end(); i++)
		{
			tmp = (*i);
			int find_open = tmp.find("[HIDDEN_BLOCK_KEY=");
			if(find_open != -1)
			{
				int find_close = tmp.find("]");
				std::string key = tmp.substr(find_open+18, find_close-18-find_open);	//HIDE KEY= 17, 1 to move to next pos
				if(key == block_name)
				{
					(*i) = block_value;
					return 1;
				}
			}
		}
		return 0;
	}

	void print()
	{
		for(std::list<std::string>::iterator i = this->mylist.begin(); i!=this->mylist.end(); i++)
		{
			std::cout << (*i) << std::endl;
		}
	}

	std::string getXMLConfig()
	{
		std::string tmp = "";
		for(std::list<std::string>::iterator i = this->mylist.begin(); i!=this->mylist.end(); i++)
		{
			tmp += (*i);
			tmp += '\n';
		}
		return tmp;
	}

private:
	std::list<std::string> mylist;
	std::map<std::string,std::string> mymap;
};

#endif
