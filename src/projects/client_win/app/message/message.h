#ifndef MESSAGE_H
#define MESSAGE_H

#include "serializable.h"

class Message : public Serializable
{
	Q_OBJECT

	Q_PROPERTY(QString typeName READ typeName WRITE setTypeName)
public:
	Q_INVOKABLE Message(QObject* parent = nullptr);
	Q_INVOKABLE Message(const Message& other);
	Q_INVOKABLE ~Message();

	Q_INVOKABLE QString typeName();
	Q_INVOKABLE void setTypeName(QString data);

	
private:
	QString _typeName;
};

Q_DECLARE_METATYPE(Message)

#endif // !MESSAGE_H
