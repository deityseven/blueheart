#ifndef SIGNINRESPONSE_H
#define SIGNINRESPONSE_H

#include "message.h"

class SigninResponse : public Message
{
	Q_OBJECT

	Q_PROPERTY(uint code READ code WRITE setCode)
	Q_PROPERTY(QString msg READ msg WRITE setMsg)

public:
	Q_INVOKABLE SigninResponse(QObject* parent = nullptr);
	Q_INVOKABLE SigninResponse(const SigninResponse& other);
	Q_INVOKABLE ~SigninResponse();

	Q_INVOKABLE uint code();
	Q_INVOKABLE void setCode(uint data);
	Q_INVOKABLE QString msg();
	Q_INVOKABLE void setMsg(QString data);


private:
	uint _code;
	QString _msg;

};

Q_DECLARE_METATYPE(SigninResponse)

#endif // !SIGNINRESPONSE_H