#ifndef ZIPERPROGRAM_H
#define ZIPERPROGRAM_H

#include <string>

class ExecutableProgram;

class ZiperProgram
{
public:
	ZiperProgram();
	~ZiperProgram();

    bool zip(std::string filePath, std::string data, std::string& msg);
    bool unZip(std::string filePath, std::string& msg);
private:
    ExecutableProgram* ep;
};

#endif // !ZIPERPROGRAM_H