#ifndef LOGINRESPONSE_H
#define LOGINRESPONSE_H

#include "message.h"

class LoginResponse : public Message
{
	Q_OBJECT

	Q_PROPERTY(bool success READ success WRITE setSuccess)

public:
	Q_INVOKABLE LoginResponse(QObject* parent = nullptr);
	Q_INVOKABLE LoginResponse(const LoginResponse& other);
	Q_INVOKABLE ~LoginResponse();

	Q_INVOKABLE bool success();
	Q_INVOKABLE void setSuccess(bool data);


private:
	bool _success;

};

Q_DECLARE_METATYPE(LoginResponse)

#endif // !LOGINRESPONSE_H