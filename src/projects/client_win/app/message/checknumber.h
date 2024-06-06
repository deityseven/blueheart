#ifndef CHECKNUMBER_H
#define CHECKNUMBER_H

#include "message.h"

class CheckNumber : public Message
{
	Q_OBJECT

	Q_PROPERTY(QString userName READ userName WRITE setUserName)
	Q_PROPERTY(QString phone READ phone WRITE setPhone)
	Q_PROPERTY(QString email READ email WRITE setEmail)
public:
	Q_INVOKABLE CheckNumber(QObject* parent = nullptr);
	Q_INVOKABLE CheckNumber(const CheckNumber& other);
	Q_INVOKABLE ~CheckNumber();

	Q_INVOKABLE QString userName();
	Q_INVOKABLE QString phone();
	Q_INVOKABLE QString email();
	Q_INVOKABLE void setUserName(QString data);
	Q_INVOKABLE void setPhone(QString data);
	Q_INVOKABLE void setEmail(QString data);

private:
	QString _userName;
	QString _phone;
	QString _email;
};

Q_DECLARE_METATYPE(CheckNumber)

#endif