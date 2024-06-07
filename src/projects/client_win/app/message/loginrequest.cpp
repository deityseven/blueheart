#include "loginrequest.h"

LoginRequest::LoginRequest(QObject * parent)
	:Message(parent)
{
}

LoginRequest::LoginRequest(const LoginRequest& other)
{
	this->_userName = other._userName;
	this->_password = other._password;

}

LoginRequest::~LoginRequest()
{
}

QString LoginRequest::userName()
{
	return this->_userName;
}

void LoginRequest::setUserName(QString data)
{
	this->_userName = data;
}
QString LoginRequest::password()
{
	return this->_password;
}

void LoginRequest::setPassword(QString data)
{
	this->_password = data;
}
