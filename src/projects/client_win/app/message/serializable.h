#ifndef serializable_H
#define serializable_H

#include <qobject.h>
#include <qstring.h>

class Serializable : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE Serializable(QObject* parent = nullptr);
    Q_INVOKABLE QString serialization();
    Q_INVOKABLE void deserialization(QString data);
};


#endif