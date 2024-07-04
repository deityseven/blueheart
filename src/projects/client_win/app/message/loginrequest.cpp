#include "loginrequest.h"

class LoginRequestPrivate
{
public:
	QString phone;
	QString email;
	QString checkNumber;
	
};

LoginRequest::LoginRequest(QObject * parent)
	:Message(parent),
	d_ptr(new LoginRequestPrivate)
{
}

LoginRequest::LoginRequest(const LoginRequest& other)
{
	this->d_ptr->phone = other.d_ptr->phone;
	this->d_ptr->email = other.d_ptr->email;
	this->d_ptr->checkNumber = other.d_ptr->checkNumber;

}

LoginRequest::~LoginRequest()
{
}

QString LoginRequest::phone()
{
	Q_D(const LoginRequest);
	return d->phone;
}

void LoginRequest::setPhone(QString phone)
{
	Q_D(LoginRequest);
	d->phone = phone;
}
QString LoginRequest::email()
{
	Q_D(const LoginRequest);
	return d->email;
}

void LoginRequest::setEmail(QString email)
{
	Q_D(LoginRequest);
	d->email = email;
}
QString LoginRequest::checkNumber()
{
	Q_D(const LoginRequest);
	return d->checkNumber;
}

void LoginRequest::setCheckNumber(QString checkNumber)
{
	Q_D(LoginRequest);
	d->checkNumber = checkNumber;
}
