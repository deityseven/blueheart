#ifndef SIGNINREQUEST_H
#define SIGNINREQUEST_H

#include "message.h"

class SigninRequest : public Message
{
	Q_OBJECT

public:
	Q_INVOKABLE SigninRequest(QObject* parent = nullptr);
	Q_INVOKABLE SigninRequest(const SigninRequest& other);
	Q_INVOKABLE ~SigninRequest();

private:
	QString _userName;
	QString _phone;
	QString _email;
	QString _checkNumber;
};

Q_DECLARE_METATYPE(SigninRequest)

#endif