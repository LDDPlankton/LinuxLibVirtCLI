#include "DAOBase.h"

DAOBase::DAOBase()
{
	this->error_message = "";
}

DAOBase::~DAOBase()
{

}

void DAOBase::setErrorMessage(string msg)
{
	this->error_message = msg;
}
string DAOBase::getErrorMessage()
{
	return this->error_message;
}
