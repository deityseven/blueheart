#ifndef SERIALIZABLETOOL_H
#define SERIALIZABLETOOL_H

#include <QWidget>
#include "ui_serializabletool.h"

class SerializableTool : public QWidget
{
    Q_OBJECT

public:
    explicit SerializableTool(QWidget *parent = nullptr);
    ~SerializableTool();

public slots:
    void build();
    void getPath();
private:
    void buildHeader();
    void buildCpp();

    QString path;
    Ui::SerializableTool ui;
};

#endif // SERIALIZABLETOOL_H
