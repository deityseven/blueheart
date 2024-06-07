#include <transmitcenter/transmitcenter.h>
#include <json/json.hpp>
#include <QMetaProperty>

TransmitCenter::TransmitCenter()
{
}

TransmitCenter& TransmitCenter::instance()
{
    static TransmitCenter ins;
    return ins;
}

TransmitCenter::~TransmitCenter()
{
}

std::string TransmitCenter::toJson(QObject * object)
{
    QString result;
    QMetaObject::invokeMethod(object, "serialization", Q_RETURN_ARG(QString, result));
    return result.toStdString();
}

QObject * TransmitCenter::fromJson(std::string data)
{
    auto root = nlohmann::json::parse(data);
    auto typeNameJson = root["typeName"];
    if (typeNameJson.is_null()) return nullptr;

    auto typeName = typeNameJson.get<std::string>();

    auto typeInt = QMetaType::type(typeName.c_str());
    auto object = static_cast<QObject*>(QMetaType::create(typeInt));

    QString arg = QString::fromStdString(data);
    QMetaObject::invokeMethod(object, "deserialization", Q_ARG(QString, arg));
    return object;
}
