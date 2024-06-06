#include "message.h"

Message::Message(QObject * parent)
    :Serializable(parent)
{
}

Message::Message(const Message& other)
{
    this->_typeName = other._typeName;
}

Message::~Message()
{
}

Q_INVOKABLE QString Message::typeName()
{
    return this->_typeName;
}

Q_INVOKABLE void Message::setTypeName(QString data)
{
    this->_typeName = data;
}
