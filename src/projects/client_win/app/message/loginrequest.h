#ifndef LOGINREQUEST_H
#define LOGINREQUEST_H

#include "message.h"

class LoginRequest : public Message
{
	Q_OBJECT

public:
	Q_INVOKABLE LoginRequest(QObject* parent = nullptr);
	Q_INVOKABLE LoginRequest(const LoginRequest& other);
	Q_INVOKABLE ~LoginRequest();

private:
	QString _userName;
	QString _password;
};

Q_DECLARE_METATYPE(LoginRequest)

#endif