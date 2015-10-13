#ifndef XMLLOADER_H_
#define XMLLOADER_H_

#include <iostream>
#include <fstream>
using namespace std;

class XMLLoader
{
public:
	XMLLoader();
	~XMLLoader();
	std::string getErrorMessage();
	bool loadXMLFile(std::string file);
	std::string getXMLContent();

private:
	std::ifstream myfile;
	std::string xml_content;
	std::string error_message;
};

#endif
