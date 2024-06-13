#ifndef EMAILSENDERCONFIG_H
#define EMAILSENDERCONFIG_H

#include <string>

class EmailSenderConfig
{
public:
    EmailSenderConfig(std::string path);
    ~EmailSenderConfig();
	std::string emailServerHost;
	std::string emailServerPort;
	std::string senderEmail;
	std::string senderKey;
};

#endif // !EMAILSENDERCONFIG_H