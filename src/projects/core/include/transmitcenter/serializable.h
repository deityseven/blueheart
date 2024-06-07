#ifndef serializable_H
#define serializable_H

#include <qobject.h>
#include <qstring.h>

class Serializable : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE Serializable(QObject* parent = nullptr);
    Q_INVOKABLE Serializable(const Serializable& other);
    Q_INVOKABLE ~Serializable();

    Q_INVOKABLE QString serialization();
    Q_INVOKABLE void deserialization(QString data);

    Serializable& operator =(const Serializable&);
};

Q_DECLARE_METATYPE(Serializable)
#endif