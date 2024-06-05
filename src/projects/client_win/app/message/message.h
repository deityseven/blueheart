#ifndef MESSAGE_H
#define MESSAGE_H

#include <qobject.h>
#include <qstring.h>

class Message : public QObject
{
	Q_OBJECT

public:
	Q_INVOKABLE Message(QObject* parent = nullptr);
	Q_INVOKABLE Message(const Message& other);
	Q_INVOKABLE ~Message();
};

Q_DECLARE_METATYPE(Message)

#endif // !MESSAGE_H
