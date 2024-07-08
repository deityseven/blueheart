#ifndef EMAILSENDERPROGRAM_H
#define EMAILSENDERPROGRAM_H

#include <string>

class ExecutableProgram;
class EmailSenderConfig;

class EmailSenderProgram
{
public:
	EmailSenderProgram(EmailSenderConfig* esc);
	~EmailSenderProgram();

    bool senderEmail(std::string recverEmail, std::string theme, std::string emailContent, std::string &msg);
private:
    bool parseResult(std::string& msg);
    ExecutableProgram* ep;
};

#endif // !EMAILSENDERPROGRAM_H