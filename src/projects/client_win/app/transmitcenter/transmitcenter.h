#ifndef TransmitCenter_H
#define TransmitCenter_H

#include <string>
#include <qobject.h>

class TransmitCenter
{
public:
    static TransmitCenter& instance();
    ~TransmitCenter();

    std::string toJson(QObject* object);
    QObject* fromJson(std::string json);
private:
    TransmitCenter();
    
};


#endif