#ifndef LOGINRESPONSE_H
#define LOGINRESPONSE_H

#include "message.h"

class LoginResponse : public Message
{
	Q_OBJECT

public:
	Q_INVOKABLE LoginResponse(QObject* parent = nullptr);
	Q_INVOKABLE LoginResponse(const LoginResponse& other);
	Q_INVOKABLE ~LoginResponse();

private:
	bool _success;
};

Q_DECLARE_METATYPE(LoginResponse)

#endif