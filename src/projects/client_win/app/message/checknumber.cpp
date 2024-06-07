#include "checknumber.h"

CheckNumber::CheckNumber(QObject * parent)
	:Message(parent)
{
}

CheckNumber::CheckNumber(const CheckNumber& other)
{
	this->_userName = other._userName;
	this->_phone = other._phone;
	this->_email = other._email;

}

CheckNumber::~CheckNumber()
{
}

QString CheckNumber::userName()
{
	return this->_userName;
}

void CheckNumber::setUserName(QString data)
{
	this->_userName = data;
}
QString CheckNumber::phone()
{
	return this->_phone;
}

void CheckNumber::setPhone(QString data)
{
	this->_phone = data;
}
QString CheckNumber::email()
{
	return this->_email;
}

void CheckNumber::setEmail(QString data)
{
	this->_email = data;
}
