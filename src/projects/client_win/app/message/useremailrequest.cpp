#include "useremailrequest.h"

class UserEmailRequestPrivate
{
public:
	QString phone;
	
};

UserEmailRequest::UserEmailRequest(QObject * parent)
	:Message(parent),
	d_ptr(new UserEmailRequestPrivate)
{
}

UserEmailRequest::UserEmailRequest(const UserEmailRequest& other)
{
	this->d_ptr->phone = other.d_ptr->phone;

}

UserEmailRequest::~UserEmailRequest()
{
}

QString UserEmailRequest::phone()
{
	Q_D(const UserEmailRequest);
	return d->phone;
}

void UserEmailRequest::setPhone(QString phone)
{
	Q_D(UserEmailRequest);
	d->phone = phone;
}
