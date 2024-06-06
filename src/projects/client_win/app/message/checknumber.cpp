#include "checknumber.h"

CheckNumber::CheckNumber(const CheckNumber &other)
{
    this->_userName = other._userName;
    this->_phone = other._phone;
    this->_email = other._email;
}

CheckNumber::CheckNumber(QObject *parent)
    :Message(parent)
{
}

CheckNumber::~CheckNumber()
{
}

Q_INVOKABLE QString CheckNumber::userName()
{
    return Q_INVOKABLE this->_userName;
}

Q_INVOKABLE QString CheckNumber::phone()
{
    return Q_INVOKABLE this->_phone;
}

Q_INVOKABLE QString CheckNumber::email()
{
    return Q_INVOKABLE this->_email;
}

Q_INVOKABLE void CheckNumber::setUserName(QString data)
{
    this->_userName = data;
}

Q_INVOKABLE void CheckNumber::setPhone(QString data)
{
    this->_phone = data;
}

Q_INVOKABLE void CheckNumber::setEmail(QString data)
{
    this->_email = data;
}
