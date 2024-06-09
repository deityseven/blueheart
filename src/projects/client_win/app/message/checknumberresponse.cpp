#include "checknumberresponse.h"

CheckNumberResponse::CheckNumberResponse(QObject * parent)
	:Message(parent)
{
}

CheckNumberResponse::CheckNumberResponse(const CheckNumberResponse& other)
{
	this->_msg = other._msg;
	this->_success = other._success;

}

CheckNumberResponse::~CheckNumberResponse()
{
}

QString CheckNumberResponse::msg()
{
	return this->_msg;
}

void CheckNumberResponse::setMsg(QString data)
{
	this->_msg = data;
}
bool CheckNumberResponse::success()
{
	return this->_success;
}

void CheckNumberResponse::setSuccess(bool data)
{
	this->_success = data;
}
