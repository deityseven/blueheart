#include <executableprogram/emailsenderprogram.h>
#include <util/platform_define.h>
#include <executableprogram/executableprogram.h>
#include <util/emailsenderconfig.h>
#include <json/json.hpp>

EmailSenderProgram::EmailSenderProgram(EmailSenderConfig* esc)
{
#ifdef I_OS_LINUX
    this->ep = new ExecutableProgram("./emailsender");
#endif
#ifdef I_OS_WIN
    this->ep = new ExecutableProgram("emailsender.exe");
#endif

    this->ep->addArg("senderEmail",esc->senderEmail);
    this->ep->addArg("senderKey",esc->senderKey);
    this->ep->addArg("emailServerHost",esc->emailServerHost);
    this->ep->addArg("emailServerPort",esc->emailServerPort);
}

EmailSenderProgram::~EmailSenderProgram()
{
    delete this->ep;
}

bool EmailSenderProgram::senderEmail(std::string recverEmail, std::string theme, std::string emailContent, std::string &msg)
{
    this->ep->addArg("recverEmail",recverEmail);
    this->ep->addArg("theme",theme);
    this->ep->addArg("emailContent",emailContent);

    return parseResult(msg);
}

bool EmailSenderProgram::parseResult(std::string &msg)
{
    std::string mysqlclientepResult = this->ep->exec();

    auto mysqlclientepResultJson = nlohmann::json::parse(mysqlclientepResult);
    bool success = mysqlclientepResultJson["success"].get<bool>();
    msg = mysqlclientepResultJson["msg"].get<std::string>();

    return success;
}
