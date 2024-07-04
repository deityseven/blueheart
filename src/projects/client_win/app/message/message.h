#ifndef MESSAGE_H
#define MESSAGE_H

#include <transmitcenter/serializable.h>

class Message : public Serializable
{
	Q_OBJECT

public:
	Q_INVOKABLE Message(QObject* parent = nullptr);
	Q_INVOKABLE Message(const Message& other);
	Q_INVOKABLE ~Message();

};

Q_DECLARE_METATYPE(Message)

#endif // !MESSAGE_H
