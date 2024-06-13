#include "signinresponse.h"

SigninResponse::SigninResponse(QObject * parent)
	:Message(parent)
{
}

SigninResponse::SigninResponse(const SigninResponse& other)
{
	this->_msg = other._msg;
	this->_success = other._success;

}

SigninResponse::~SigninResponse()
{
}

QString SigninResponse::msg()
{
	return this->_msg;
}

void SigninResponse::setMsg(QString data)
{
	this->_msg = data;
}
bool SigninResponse::success()
{
	return this->_success;
}

void SigninResponse::setSuccess(bool data)
{
	this->_success = data;
}
