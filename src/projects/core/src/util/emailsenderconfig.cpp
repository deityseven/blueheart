#include <util/emailsenderconfig.h>
#include <configfile/config_file.h>

EmailSenderConfig::EmailSenderConfig(std::string path)
{
    ConfigFile cf(path);
	cf.beginSection("EmailSender");
	this->emailServerHost = cf.value("emailServerHost").toString();
	this->emailServerPort = cf.value("emailServerPort").toString();
	this->senderEmail = cf.value("senderEmail").toString();
	this->senderKey = cf.value("senderKey").toString();
	cf.endSection();
}

EmailSenderConfig::~EmailSenderConfig()
{
}
