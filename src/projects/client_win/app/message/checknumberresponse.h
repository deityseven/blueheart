#ifndef CHECKNUMBERRESPONSE_H
#define CHECKNUMBERRESPONSE_H

#include "message.h"

class CheckNumberResponse : public Message
{
	Q_OBJECT

	Q_PROPERTY(QString msg READ msg WRITE setMsg)
	Q_PROPERTY(bool success READ success WRITE setSuccess)

public:
	Q_INVOKABLE CheckNumberResponse(QObject* parent = nullptr);
	Q_INVOKABLE CheckNumberResponse(const CheckNumberResponse& other);
	Q_INVOKABLE ~CheckNumberResponse();

	Q_INVOKABLE QString msg();
	Q_INVOKABLE void setMsg(QString data);
	Q_INVOKABLE bool success();
	Q_INVOKABLE void setSuccess(bool data);


private:
	QString _msg;
	bool _success;

};

Q_DECLARE_METATYPE(CheckNumberResponse)

#endif // !CHECKNUMBERRESPONSE_H