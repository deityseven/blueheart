#include "checknumberrequest.h"

CheckNumberRequest::CheckNumberRequest(QObject * parent)
	:Message(parent)
{
}

CheckNumberRequest::CheckNumberRequest(const CheckNumberRequest& other)
{
	this->_userName = other._userName;
	this->_phone = other._phone;
	this->_email = other._email;

}

CheckNumberRequest::~CheckNumberRequest()
{
}

QString CheckNumberRequest::userName()
{
	return this->_userName;
}

void CheckNumberRequest::setUserName(QString data)
{
	this->_userName = data;
}
QString CheckNumberRequest::phone()
{
	return this->_phone;
}

void CheckNumberRequest::setPhone(QString data)
{
	this->_phone = data;
}
QString CheckNumberRequest::email()
{
	return this->_email;
}

void CheckNumberRequest::setEmail(QString data)
{
	this->_email = data;
}
