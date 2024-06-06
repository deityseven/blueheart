#ifndef SIGNINREQUEST_H
#define SIGNINREQUEST_H

#include "message.h"
#include "checknumber.h"

class SigninRequest : public Message
{
	Q_OBJECT

	Q_PROPERTY(QString userName READ userName WRITE setUserName)
	Q_PROPERTY(QString phone READ phone WRITE setPhone)
	Q_PROPERTY(QString email READ email WRITE setEmail)
	Q_PROPERTY(QString checkNumber READ checkNumber WRITE setCheckNumber)
	Q_PROPERTY(CheckNumber ch READ ch WRITE setCh)
public:
	Q_INVOKABLE SigninRequest(const SigninRequest& other);
	Q_INVOKABLE SigninRequest(QObject* parent = nullptr);
	Q_INVOKABLE ~SigninRequest();

	Q_INVOKABLE QString userName();
	Q_INVOKABLE QString phone();
	Q_INVOKABLE QString email();
	Q_INVOKABLE QString checkNumber();
	Q_INVOKABLE CheckNumber ch();
	Q_INVOKABLE void setUserName(QString data);
	Q_INVOKABLE void setPhone(QString data);
	Q_INVOKABLE void setEmail(QString data);
	Q_INVOKABLE void setCheckNumber(QString data);
	Q_INVOKABLE void setCh(CheckNumber data);

private:
	QString _userName;
	QString _phone;
	QString _email;
	QString _checkNumber;
	CheckNumber _ch;
};

Q_DECLARE_METATYPE(SigninRequest)

#endif