#ifndef DAOBASE_H_
#define DAOBASE_H_

#include <iostream>
#include "Helpers/StringHelper.h"
using namespace std;

class DAOBase
{
public:
	StringHelper strhelper;

	DAOBase();
	~DAOBase();
	void setErrorMessage(string msg);
	string getErrorMessage();
private:
	string error_message;
};

#endif
