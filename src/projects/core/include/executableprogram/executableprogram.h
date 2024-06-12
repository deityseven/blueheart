#ifndef EXECUTABLEPROGRAM_H
#define EXECUTABLEPROGRAM_H

#include <string>
#include <map>

class ExecutableProgram
{
public:
	ExecutableProgram(std::string programPath);
	~ExecutableProgram();

    void addArg(std::string arg, std::string value);
    std::string exec();

private:
    std::string path;
    std::map<std::string, std::string> args;
};

#endif // !EXECUTABLEPROGRAM_H