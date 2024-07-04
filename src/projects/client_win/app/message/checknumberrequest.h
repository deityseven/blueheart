#ifndef CHECKNUMBERREQUEST_H
#define CHECKNUMBERREQUEST_H

#include "message.h"

class CheckNumberRequestPrivate;

class CheckNumberRequest : public Message
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(CheckNumberRequest)
	Q_PROPERTY(QString userName READ userName WRITE setUserName)
	Q_PROPERTY(QString phone READ phone WRITE setPhone)
	Q_PROPERTY(QString email READ email WRITE setEmail)

public:
	Q_INVOKABLE CheckNumberRequest(QObject* parent = nullptr);
	Q_INVOKABLE CheckNumberRequest(const CheckNumberRequest& other);
	Q_INVOKABLE ~CheckNumberRequest();

	Q_INVOKABLE QString userName();
	Q_INVOKABLE void setUserName(QString data);
	Q_INVOKABLE QString phone();
	Q_INVOKABLE void setPhone(QString data);
	Q_INVOKABLE QString email();
	Q_INVOKABLE void setEmail(QString data);


private:
	QScopedPointer<CheckNumberRequestPrivate> d_ptr;
};

Q_DECLARE_METATYPE(CheckNumberRequest)

#endif // !CHECKNUMBERREQUEST_H