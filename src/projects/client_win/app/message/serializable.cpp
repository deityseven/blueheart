#include "serializable.h"
#include <vector>
#include <string>
#include <algorithm>

#include <json/json.hpp>
#include <QMetaProperty>

std::vector<std::string> userDefineType = {
"Message",
"CheckNumber"
};

Serializable::Serializable(QObject* parent = nullptr)
    :QObject(parent)
{
}

QString Serializable::serialization()
{
    nlohmann::json root;

    auto metaObject = this->metaObject();
    root["objectType"] = metaObject->className();

    for(auto i = 0; metaObject->propertyCount(); ++i)
    {
        QMetaProperty property = metaObject->property(i);
        auto propertyName = property.name();
        auto propertyTypeName = property.typeName();
        auto typeNameIter = std::find(userDefineType.begin(), userDefineType.end(), propertyTypeName);
        if(typeNameIter != userDefineType.end())
        {
            QString result;
            QGenericReturnArgument ret("result", &result);
            QMetaObject::invokeMethod(qobject_cast<QObject*>(this), "serialization" , Qt::DirectConnection, ret);
            root[propertyName] = result.toStdString();
        }
        root[propertyName] = this->property(propertyName).toString().toStdString();
    }

    return QString::fromStdString(root.dump());
}

void Serializable::deserialization(QString data)
{
    return void();
}
