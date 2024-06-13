#ifndef SIGNINRESPONSE_H
#define SIGNINRESPONSE_H

#include "message.h"

class SigninResponse : public Message
{
	Q_OBJECT

	Q_PROPERTY(QString msg READ msg WRITE setMsg)
	Q_PROPERTY(bool success READ success WRITE setSuccess)

public:
	Q_INVOKABLE SigninResponse(QObject* parent = nullptr);
	Q_INVOKABLE SigninResponse(const SigninResponse& other);
	Q_INVOKABLE ~SigninResponse();

	Q_INVOKABLE QString msg();
	Q_INVOKABLE void setMsg(QString data);
	Q_INVOKABLE bool success();
	Q_INVOKABLE void setSuccess(bool data);


private:
	QString _msg;
	bool _success;

};

Q_DECLARE_METATYPE(SigninResponse)

#endif // !SIGNINRESPONSE_H