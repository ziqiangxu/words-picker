#ifndef ABOUT_H
#define ABOUT_H

#include <QMainWindow>
#include <QTextBrowser>
#include <QPushButton>
#include <QSettings>
#include "word_table.h"
class About : public QWidget
{
    Q_OBJECT
public:
    explicit About(QWidget *parent = nullptr);
    ~About();

    QTextBrowser *help;
    QPushButton *derive;
    QPushButton *update;
    Word_table *word_table;
    QSettings *info;     // 读取信息
    int version_main;         // 主要版本号
    int version_subordinate;  // 次要版本号

signals:

public slots:
    void get_update();
    void manage_new();
private:
    void buildGUI();
    QString help_text();
};

#endif // ABOUT_H
