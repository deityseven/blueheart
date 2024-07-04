#ifndef RESPONSE_H
#define RESPONSE_H

#include "message.h"

class ResponsePrivate;

class Response : public Message
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(Response)
	Q_PROPERTY(bool success READ success WRITE setSuccess)
	Q_PROPERTY(QString msg READ msg WRITE setMsg)

public:
	Q_INVOKABLE Response(QObject* parent = nullptr);
	Q_INVOKABLE Response(const Response& other);
	Q_INVOKABLE ~Response();

	Q_INVOKABLE bool success();
	Q_INVOKABLE void setSuccess(bool data);
	Q_INVOKABLE QString msg();
	Q_INVOKABLE void setMsg(QString data);


private:
	QScopedPointer<ResponsePrivate> d_ptr;
};

Q_DECLARE_METATYPE(Response)

#endif // !RESPONSE_H