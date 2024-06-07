#include "loginresponse.h"

LoginResponse::LoginResponse(QObject * parent)
	:Message(parent)
{
}

LoginResponse::LoginResponse(const LoginResponse& other)
{
	this->_success = other._success;

}

LoginResponse::~LoginResponse()
{
}

bool LoginResponse::success()
{
	return this->_success;
}

void LoginResponse::setSuccess(bool data)
{
	this->_success = data;
}
