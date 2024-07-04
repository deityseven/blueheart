#include "checknumberrequest.h"

class CheckNumberRequestPrivate
{
public:
	QString userName;
	QString phone;
	QString email;
	
};

CheckNumberRequest::CheckNumberRequest(QObject * parent)
	:Message(parent),
	d_ptr(new CheckNumberRequestPrivate)
{
}

CheckNumberRequest::CheckNumberRequest(const CheckNumberRequest& other)
{
	this->d_ptr->userName = other.d_ptr->userName;
	this->d_ptr->phone = other.d_ptr->phone;
	this->d_ptr->email = other.d_ptr->email;

}

CheckNumberRequest::~CheckNumberRequest()
{
}

QString CheckNumberRequest::userName()
{
	Q_D(const CheckNumberRequest);
	return d->userName;
}

void CheckNumberRequest::setUserName(QString userName)
{
	Q_D(CheckNumberRequest);
	d->userName = userName;
}
QString CheckNumberRequest::phone()
{
	Q_D(const CheckNumberRequest);
	return d->phone;
}

void CheckNumberRequest::setPhone(QString phone)
{
	Q_D(CheckNumberRequest);
	d->phone = phone;
}
QString CheckNumberRequest::email()
{
	Q_D(const CheckNumberRequest);
	return d->email;
}

void CheckNumberRequest::setEmail(QString email)
{
	Q_D(CheckNumberRequest);
	d->email = email;
}
