#include "message.h"

Message::Message(QObject * parent)
    :Serializable(parent)
{
}

Message::Message(const Message& other)
    :Serializable(other)
{
}

Message::~Message()
{
}
