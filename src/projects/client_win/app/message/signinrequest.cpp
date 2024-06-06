#include "signinrequest.h"

SigninRequest::SigninRequest(const SigninRequest &other)
{
}

SigninRequest::SigninRequest(QObject *parent)
{
}

SigninRequest::~SigninRequest()
{
}


Q_INVOKABLE QString SigninRequest::userName()
{
    return Q_INVOKABLE this->_userName;
}

Q_INVOKABLE QString SigninRequest::phone()
{
    return Q_INVOKABLE this->_phone;
}

Q_INVOKABLE QString SigninRequest::email()
{
    return Q_INVOKABLE this->_email;
}

Q_INVOKABLE QString SigninRequest::checkNumber()
{
    return Q_INVOKABLE this->_checkNumber;
}

Q_INVOKABLE CheckNumber SigninRequest::ch()
{
    return Q_INVOKABLE this->_ch;
}

Q_INVOKABLE void SigninRequest::setUserName(QString data)
{
    this->_userName = data;
}

Q_INVOKABLE void SigninRequest::setPhone(QString data)
{
    this->_phone = data;
}

Q_INVOKABLE void SigninRequest::setEmail(QString data)
{
    this->_email = data;
}

Q_INVOKABLE void SigninRequest::setCheckNumber(QString data)
{
    this->_checkNumber = data;
}

Q_INVOKABLE void SigninRequest::setCh(CheckNumber data)
{
    this->_ch = data;
}
