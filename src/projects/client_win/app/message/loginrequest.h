#ifndef LOGINREQUEST_H
#define LOGINREQUEST_H

#include "message.h"

class LoginRequest : public Message
{
	Q_OBJECT

	Q_PROPERTY(QString userName READ userName WRITE setUserName)
	Q_PROPERTY(QString password READ password WRITE setPassword)

public:
	Q_INVOKABLE LoginRequest(QObject* parent = nullptr);
	Q_INVOKABLE LoginRequest(const LoginRequest& other);
	Q_INVOKABLE ~LoginRequest();

	Q_INVOKABLE QString userName();
	Q_INVOKABLE void setUserName(QString data);
	Q_INVOKABLE QString password();
	Q_INVOKABLE void setPassword(QString data);


private:
	QString _userName;
	QString _password;

};

Q_DECLARE_METATYPE(LoginRequest)

#endif // !LOGINREQUEST_H