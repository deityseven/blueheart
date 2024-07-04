#include <transmitcenter/serializable.h>
#include <vector>
#include <string>
#include <algorithm>

#include <json/json.hpp>
#include <QMetaProperty>
#include <qarraydata.h>
#include <qdebug.h>
#include <QObject>

struct SerializablePrivate
{
	QString typeName;
};

Serializable::Serializable(QObject* parent)
	:QObject(parent),
	d_ptr(new SerializablePrivate)
{
}

Serializable::Serializable(const Serializable &other)
{
	this->d_ptr->typeName = other.d_ptr->typeName;
}

Serializable::~Serializable()
{
}

QString Serializable::serialization()
{
	nlohmann::json root;

	auto metaObject = this->metaObject();
	root["typeName"] = metaObject->className();

	for (auto i = 0; i < metaObject->propertyCount(); ++i)
	{
		QMetaProperty property = metaObject->property(i);
		auto propertyName = property.name();
		if (strcmp(propertyName, "objectName") == 0) continue;
		if (strcmp(propertyName, "typeName") == 0) continue;

		auto propertyTypeName = property.typeName();
		if (property.type() == QVariant::UserType)
		{
			QString result;
			QMetaObject::invokeMethod(static_cast<QObject*>(this->property(propertyName).data()), "serialization", Q_RETURN_ARG(QString, result));
			root[propertyName] = nlohmann::json::parse(result.toStdString());
		}
		else
		{
			root[propertyName] = this->property(propertyName).toString().toStdString();
		}
	}

	return QString::fromStdString(root.dump());
}

void Serializable::deserialization(QString data)
{
	auto root = nlohmann::json::parse(data.toStdString());

	for (auto iter = root.begin(); iter != root.end(); ++iter)
	{
		auto key = iter.key();
		auto value = iter.value();
		if (value.is_object())
		{
			std::string values = value.dump();
			QString arg = QString::fromStdString(value.dump());

			auto propertyVariant = this->property(key.c_str());
			auto propertyObject = static_cast<QObject*>(propertyVariant.data());
			QMetaObject::invokeMethod(propertyObject, "deserialization", Q_ARG(QString, arg));
			this->setProperty(key.c_str(), propertyVariant);
		}
		else
		{
			if (value.type() == nlohmann::json::value_t::null)
			{
			}
			else if (value.type() == nlohmann::json::value_t::array)
			{
			}
			else if (value.type() == nlohmann::json::value_t::string)
			{
				this->setProperty(key.c_str(), QString::fromStdString(value.get<std::string>()));
			}
			else if (value.type() == nlohmann::json::value_t::boolean)
			{
				this->setProperty(key.c_str(), value.get<bool>());
			}
			else if (value.type() == nlohmann::json::value_t::number_integer)
			{
				this->setProperty(key.c_str(), value.get<int>());
			}
			else if (value.type() == nlohmann::json::value_t::number_unsigned)
			{
				this->setProperty(key.c_str(), value.get<unsigned int>());
			}
			else if (value.type() == nlohmann::json::value_t::number_float)
			{
				this->setProperty(key.c_str(), value.get<double>());
			}
		}
	}
}

QString Serializable::typeName()
{
	Q_D(const Serializable);
	return d->typeName;
}

void Serializable::setTypeName(QString typeName)
{
	Q_D(Serializable);
	d->typeName = typeName;
}

