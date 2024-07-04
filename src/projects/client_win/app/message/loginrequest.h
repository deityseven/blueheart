#ifndef LOGINREQUEST_H
#define LOGINREQUEST_H

#include "message.h"

class LoginRequestPrivate;

class LoginRequest : public Message
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(LoginRequest)
	Q_PROPERTY(QString phone READ phone WRITE setPhone)
	Q_PROPERTY(QString email READ email WRITE setEmail)
	Q_PROPERTY(QString checkNumber READ checkNumber WRITE setCheckNumber)

public:
	Q_INVOKABLE LoginRequest(QObject* parent = nullptr);
	Q_INVOKABLE LoginRequest(const LoginRequest& other);
	Q_INVOKABLE ~LoginRequest();

	Q_INVOKABLE QString phone();
	Q_INVOKABLE void setPhone(QString data);
	Q_INVOKABLE QString email();
	Q_INVOKABLE void setEmail(QString data);
	Q_INVOKABLE QString checkNumber();
	Q_INVOKABLE void setCheckNumber(QString data);


private:
	QScopedPointer<LoginRequestPrivate> d_ptr;
};

Q_DECLARE_METATYPE(LoginRequest)

#endif // !LOGINREQUEST_H