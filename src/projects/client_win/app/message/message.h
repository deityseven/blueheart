#ifndef MESSAGE_H
#define MESSAGE_H

#include "serializable.h"
#include <qobject.h>

class Message : public Serializable
{
public:
	Q_INVOKABLE Message(QObject* parent = nullptr);
	Q_INVOKABLE Message(const Message& other);
	Q_INVOKABLE ~Message();
};

Q_DECLARE_METATYPE(Message)

#endif // !MESSAGE_H
