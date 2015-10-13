#include "XMLLoader.h"

XMLLoader::XMLLoader()
{
	this->xml_content = "";
	this->error_message = "";
}

XMLLoader::~XMLLoader()
{

}

std::string XMLLoader::getErrorMessage()
{
	return this->error_message;
}

/*
 * This function will load a LibVirt XML file, into a buffer. Should not use, use LibVirtAPI [Deprec]
 *
 * @param string file
 * @return bool
 */
bool XMLLoader::loadXMLFile(std::string file)
{
	std::string file_real = "/etc/libvirt/qemu/" + file + ".xml";
	this->myfile.open(file_real.c_str(), std::ios::in);
	if(!myfile)
	{
		this->error_message = "Error: XMLLoader::loadXMLFile() - Failed to load XMLFile [" + file_real + "]";
		return false;
	}
	//LOOP + ADD LINE
	char line[1024];
	while( myfile.getline(line,1024) )
	{
		std::string tmp = std::string(line);
		this->xml_content += tmp;
		cout << tmp << endl;
	}
	this->myfile.close();

	return true;
}

std::string XMLLoader::getXMLContent()
{
	return this->xml_content;
}
