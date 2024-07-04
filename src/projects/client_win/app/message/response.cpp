#include "response.h"

class ResponsePrivate
{
public:
	bool success;
	QString msg;
	
};

Response::Response(QObject * parent)
	:Message(parent),
	d_ptr(new ResponsePrivate)
{
}

Response::Response(const Response& other)
{
	this->d_ptr->success = other.d_ptr->success;
	this->d_ptr->msg = other.d_ptr->msg;

}

Response::~Response()
{
}

bool Response::success()
{
	Q_D(const Response);
	return d->success;
}

void Response::setSuccess(bool success)
{
	Q_D(Response);
	d->success = success;
}
QString Response::msg()
{
	Q_D(const Response);
	return d->msg;
}

void Response::setMsg(QString msg)
{
	Q_D(Response);
	d->msg = msg;
}
