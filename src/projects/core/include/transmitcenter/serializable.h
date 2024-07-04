#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <qobject.h>
#include <qstring.h>

class SerializablePrivate;

class Serializable : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Serializable)
	Q_PROPERTY(QString typeName READ typeName WRITE setTypeName)

public:
    Q_INVOKABLE Serializable(QObject* parent = nullptr);
    Q_INVOKABLE Serializable(const Serializable& other);
    Q_INVOKABLE ~Serializable();

    Q_INVOKABLE QString serialization();
    Q_INVOKABLE void deserialization(QString data);

	Q_INVOKABLE QString typeName();
	Q_INVOKABLE void setTypeName(QString data);

private:
    QScopedPointer<SerializablePrivate> d_ptr;
};

Q_DECLARE_METATYPE(Serializable)
#endif