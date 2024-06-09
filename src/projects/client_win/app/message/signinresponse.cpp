#include "signinresponse.h"

SigninResponse::SigninResponse(QObject * parent)
	:Message(parent)
{
}

SigninResponse::SigninResponse(const SigninResponse& other)
{
	this->_code = other._code;
	this->_msg = other._msg;

}

SigninResponse::~SigninResponse()
{
}

uint SigninResponse::code()
{
	return this->_code;
}

void SigninResponse::setCode(uint data)
{
	this->_code = data;
}
QString SigninResponse::msg()
{
	return this->_msg;
}

void SigninResponse::setMsg(QString data)
{
	this->_msg = data;
}
