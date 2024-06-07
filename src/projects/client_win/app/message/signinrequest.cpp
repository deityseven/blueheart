#include "signinrequest.h"

SigninRequest::SigninRequest(QObject * parent)
	:Message(parent)
{
}

SigninRequest::SigninRequest(const SigninRequest& other)
{
	this->_userName = other._userName;
	this->_phone = other._phone;
	this->_email = other._email;
	this->_checkNumber = other._checkNumber;

}

SigninRequest::~SigninRequest()
{
}

QString SigninRequest::userName()
{
	return this->_userName;
}

void SigninRequest::setUserName(QString data)
{
	this->_userName = data;
}
QString SigninRequest::phone()
{
	return this->_phone;
}

void SigninRequest::setPhone(QString data)
{
	this->_phone = data;
}
QString SigninRequest::email()
{
	return this->_email;
}

void SigninRequest::setEmail(QString data)
{
	this->_email = data;
}
QString SigninRequest::checkNumber()
{
	return this->_checkNumber;
}

void SigninRequest::setCheckNumber(QString data)
{
	this->_checkNumber = data;
}
