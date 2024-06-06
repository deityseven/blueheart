#include "transmitcenter.h"
#include <json/json.hpp>
#include <QMetaProperty>

TransmitCenter::TransmitCenter()
{
}

TransmitCenter::~TransmitCenter()
{
}

std::string TransmitCenter::toJson(QObject * object)
{
    nlohmann::json root;

    auto metaObject = object->metaObject();
    root["objectType"] = metaObject->className();

    for(auto i = 0; metaObject->propertyCount(); ++i)
    {
        QMetaProperty property = metaObject->property(i);
        auto propertyName = property.name();
        auto propertyType = property.type();
        root[propertyName] = object->property(propertyName).toString().toStdString();
    }




    return std::string();
}

QObject * TransmitCenter::fromJson(std::string json)
{
return nullptr;
}
