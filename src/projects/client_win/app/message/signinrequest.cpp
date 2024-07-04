#include "signinrequest.h"

class SigninRequestPrivate
{
public:
	QString userName;
	QString phone;
	QString email;
	QString checkNumber;
	
};

SigninRequest::SigninRequest(QObject * parent)
	:Message(parent),
	d_ptr(new SigninRequestPrivate)
{
}

SigninRequest::SigninRequest(const SigninRequest& other)
{
	this->d_ptr->userName = other.d_ptr->userName;
	this->d_ptr->phone = other.d_ptr->phone;
	this->d_ptr->email = other.d_ptr->email;
	this->d_ptr->checkNumber = other.d_ptr->checkNumber;

}

SigninRequest::~SigninRequest()
{
}

QString SigninRequest::userName()
{
	Q_D(const SigninRequest);
	return d->userName;
}

void SigninRequest::setUserName(QString userName)
{
	Q_D(SigninRequest);
	d->userName = userName;
}
QString SigninRequest::phone()
{
	Q_D(const SigninRequest);
	return d->phone;
}

void SigninRequest::setPhone(QString phone)
{
	Q_D(SigninRequest);
	d->phone = phone;
}
QString SigninRequest::email()
{
	Q_D(const SigninRequest);
	return d->email;
}

void SigninRequest::setEmail(QString email)
{
	Q_D(SigninRequest);
	d->email = email;
}
QString SigninRequest::checkNumber()
{
	Q_D(const SigninRequest);
	return d->checkNumber;
}

void SigninRequest::setCheckNumber(QString checkNumber)
{
	Q_D(SigninRequest);
	d->checkNumber = checkNumber;
}
