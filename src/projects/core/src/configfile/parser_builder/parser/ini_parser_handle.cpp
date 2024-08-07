#include "ini_parser_handle.h"
#include <util/file_util.h>
#include <util/string_util.h>

IniParserHandle::IniParserHandle()
{
}

bool IniParserHandle::canHandle(const ConfigFileType & type)
{
    return type == ConfigFileType::Ini;
}

bool IniParserHandle::handle(const std::string & content, std::map<std::string, std::map<std::string, Data>>& data)
{
    //在文件内容末尾添加新行方便解析
    //add a newline at the end of the file
    std::string fileData = content + '\n';

    std::list<std::string> list = StringUtil::split(fileData, '\n');

    std::string sectionName = "default";

    for (auto iter = list.begin(); iter != list.end(); ++iter)
    {
        auto& line = (*iter);
        //空行处理
        if (line.empty()) continue;

        //不需要解析注释行
        //needn't parse annotation line
        if (line.find('#') != std::string::npos) continue;

        //这一行是key和value，解析他们保存到当前sectionname段下
        //this line is key and value, parse they save to current sectionName.
        if (line.find('=') != std::string::npos)
        {
            std::list<std::string> keyAndValue = StringUtil::split(line, '=');
            if (keyAndValue.empty()) continue;

            auto iter = keyAndValue.begin();

            std::string key = *iter;
            Data value(*(++iter));

            data[sectionName][key] = value;
        }

        //这行是sectionname
        //this line is section name
        if (line.find('[') != std::string::npos && line.find(']') != std::string::npos)
        {
            //移除[]，并给当前段赋值为sectionName
            //drop []
            sectionName = std::string(line.begin() + 1, line.end() - 1);
        }
    }

    return true;
}