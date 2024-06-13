#include <util/mysqlserverconfig.h>
#include <configfile/config_file.h>

MysqlServerConfig::MysqlServerConfig(std::string path)
{
    ConfigFile cf(path);
	cf.beginSection("MysqlServer");
	this->serverHost = cf.value("host").toString();
	this->serverPort = cf.value("port").toString();
	this->userName = cf.value("userName").toString();
	this->password = cf.value("password").toString();
	this->database = cf.value("database").toString();
	cf.endSection();
}

MysqlServerConfig::~MysqlServerConfig()
{
}
