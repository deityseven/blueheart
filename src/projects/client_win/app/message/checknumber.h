#ifndef CHECKNUMBER_H
#define CHECKNUMBER_H

#include "message.h"

class CheckNumber : public Message
{
	Q_OBJECT

public:
	Q_INVOKABLE CheckNumber(QObject* parent = nullptr);
	Q_INVOKABLE CheckNumber(const CheckNumber& other);
	Q_INVOKABLE ~CheckNumber();

private:
	QString _userName;
	QString _phone;
	QString _email;
};

Q_DECLARE_METATYPE(CheckNumber)

#endif