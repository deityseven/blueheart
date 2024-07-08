#ifndef MYSQLPROGRAM_H
#define MYSQLPROGRAM_H

#include <string>

class ExecutableProgram;
class MysqlServerConfig;

class MysqlProgram
{
public:
	MysqlProgram(MysqlServerConfig* msc);
	~MysqlProgram();

    bool queryUserNameIsExist(std::string jsonData, std::string &msg);
    bool addUserInfo(std::string jsonData, std::string &msg);
    bool checkNumberCompare(std::string jsonData, std::string &msg);
    bool updateUserPassword(std::string jsonData, std::string &msg);
private:
    ExecutableProgram* ep;
};

#endif // !MYSQLPROGRAM_H