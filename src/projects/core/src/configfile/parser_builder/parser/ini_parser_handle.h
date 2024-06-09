#ifndef INI_PARSER_HANDLE_H
#define INI_PARSER_HANDLE_H

#include "config_file_content_parser_handle.h"

class IniParserHandle : public ConfigFileContentParserHandle
{
public:
    IniParserHandle();

protected:

    // 通过 ConfigFileContentParserHandle 继承
    virtual bool canHandle(const ConfigFileType & type) override;
    virtual bool handle(const std::string & data, std::map<std::string, std::map<std::string, Data>>& out) override;
};

#endif // !CONFIG_FILE_H