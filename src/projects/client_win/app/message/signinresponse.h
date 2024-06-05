#ifndef SIGNINRESPONSE_H
#define SIGNINRESPONSE_H

#include "message.h"

class SigninResponse : public Message
{
	Q_OBJECT

public:
	Q_INVOKABLE SigninResponse(QObject* parent = nullptr);
	Q_INVOKABLE SigninResponse(const SigninResponse& other);
	Q_INVOKABLE ~SigninResponse();

private:
	unsigned int _code;
	QString _msg;
};

Q_DECLARE_METATYPE(SigninResponse)

#endif