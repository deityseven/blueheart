#ifndef USEREMAILREQUEST_H
#define USEREMAILREQUEST_H

#include "message.h"

class UserEmailRequestPrivate;

class UserEmailRequest : public Message
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(UserEmailRequest)
	Q_PROPERTY(QString phone READ phone WRITE setPhone)

public:
	Q_INVOKABLE UserEmailRequest(QObject* parent = nullptr);
	Q_INVOKABLE UserEmailRequest(const UserEmailRequest& other);
	Q_INVOKABLE ~UserEmailRequest();

	Q_INVOKABLE QString phone();
	Q_INVOKABLE void setPhone(QString data);


private:
	QScopedPointer<UserEmailRequestPrivate> d_ptr;
};

Q_DECLARE_METATYPE(UserEmailRequest)

#endif // !USEREMAILREQUEST_H