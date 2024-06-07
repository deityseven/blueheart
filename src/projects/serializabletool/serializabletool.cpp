#include "serializabletool.h"
#include <qdebug.h>
#include <qfiledialog.h>
#include <QFile>
#include <QTextStream>

const char* headerTempldate = 
"#ifndef %1\n#define %1\n\n#include \"message.h\"\n\nclass %0 : public Message\n{\n\tQ_OBJECT\n\n%2\npublic:\n\tQ_INVOKABLE %0(QObject* parent = nullptr);\n\tQ_INVOKABLE %0(const %0& other);\n\tQ_INVOKABLE ~%0();\n\n%3\n\nprivate:\n%4\n};\n\nQ_DECLARE_METATYPE(%0)\n\n#endif // !%1";

const char* propertyTemplate = 
"\tQ_PROPERTY(%0 %1 READ %1 WRITE %2)\n";

const char* propertyFunctionTemplate = 
"\tQ_INVOKABLE %0 %1();\n\tQ_INVOKABLE void %2(%0 data);\n";

const char* propertyMemberVariableTemplate = 
"\t%0 _%1;\n";

bool saveTextFile(const QString &fileName, const QString &text) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return false; // 无法打开文件
    }
 
    QTextStream out(&file);
    out << text;
    file.close();
    return true;
}

SerializableTool::SerializableTool(QWidget *parent) :
    QWidget(parent)
{
    ui.setupUi(this);

    connect(this->ui.build,SIGNAL(clicked()),this,SLOT(build()));
    connect(this->ui.path,SIGNAL(clicked()),this,SLOT(getPath()));
}

SerializableTool::~SerializableTool()
{
}

void SerializableTool::getPath()
{
    this->path = QFileDialog::getExistingDirectory(this);
}

void SerializableTool::build()
{
    buildHeader();
    buildCpp();
}

void SerializableTool::buildHeader()
{
    //%0 类名
    //%1 类宏
    //%2 属性宏
    //%3 属性方法声明
    //%4 属性成员变量
    QString className = this->ui.className->text();
    QString classMacro = QString(className + "_h").toUpper();

    QStringList propertyList = this->ui.propertyList->toPlainText().split("\n");
    QString propertyMacro;
    QString propertyFunctionStatement;
    QString propertyMemberVariable;

    for(auto property : propertyList)
    {
        if(property.isEmpty()) continue;

        auto propertyList = property.split(",");

        auto propertyTypeName = propertyList.front();
        auto getProperty = propertyList.last();
        auto propertyName = getProperty;
        propertyName.front() = propertyName.front().toUpper();
        auto setProperty = "set" + propertyName;
        //%0 类型
        //%1 get方法
        //%2 set方法
        propertyMacro += QString(propertyTemplate).arg(propertyTypeName).arg(getProperty).arg(setProperty);
        //%0 类型
        //%1 get方法
        //%2 set方法
        propertyFunctionStatement += QString(propertyFunctionTemplate).arg(propertyTypeName).arg(getProperty).arg(setProperty);

        propertyMemberVariable += QString(propertyMemberVariableTemplate).arg(propertyTypeName).arg(getProperty);
    }

    QString headerFile = QString(headerTempldate).arg(className).arg(classMacro).arg(propertyMacro).arg(propertyFunctionStatement).arg(propertyMemberVariable);

    QString fileName = className.toLower() + ".h";

    saveTextFile(this->path + "/" + fileName, headerFile);
}

const char* cppTemplate = 
"#include \"%0\"\n\n%1::%1(QObject * parent)\n\t:Message(parent)\n{\n}\n\n%1::%1(const %1& other)\n{\n%3\n}\n\n%1::~%1()\n{\n}\n\n%4";

const char* copyFunctionTemplate = 
"\tthis->_%0 = other._%0;\n";

const char* propertyImplTemplate = 
"%0 %1::%2()\n{\n\treturn this->_%2;\n}\n\nvoid %1::%3(%0 data)\n{\n\tthis->_%2 = data;\n}\n";

void SerializableTool::buildCpp()
{
    //%0 headerFileName
    //%1 className
    //%3 copyFunction
    //%4 propertyImpl
    QString className = this->ui.className->text();
    QString headerFileName = QString(className + ".h").toLower();

    QStringList propertyList = this->ui.propertyList->toPlainText().split("\n");
    QString copyFunction;
    QString propertyImpl;

    for(auto property : propertyList)
    {
        if(property.isEmpty()) continue;

        auto propertyList = property.split(",");

        auto propertyTypeName = propertyList.front();
        auto getProperty = propertyList.last();
        auto propertyName = getProperty;
        propertyName.front() = propertyName.front().toUpper();
        auto setProperty = "set" + propertyName;

        //%0 get方法
        copyFunction += QString(copyFunctionTemplate).arg(getProperty);
        //%0 属性类型
        //%1 类名
        //%2 get方法
        //%3 set方法
        propertyImpl += QString(propertyImplTemplate).arg(propertyTypeName).arg(className).arg(getProperty).arg(setProperty);
    }
    
    QString cppFile = QString(cppTemplate).arg(headerFileName).arg(className).arg(copyFunction).arg(propertyImpl);

    QString fileName = className.toLower() + ".cpp";

    saveTextFile(this->path + "/" + fileName, cppFile);
}

