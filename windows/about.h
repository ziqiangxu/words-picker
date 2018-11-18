#ifndef ABOUT_H
#define ABOUT_H

#include <QMainWindow>
#include <QTextBrowser>
#include <QPushButton>
#include <QSettings>
#include "word_table.h"
#include <QtNetwork>

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
    QSettings *info;          // 读取信息
    QSettings *info_;         // 从github下载下来的info文件
    int version_main;         // 主要版本号
    int version_subordinate;  // 次要版本号

private:
    QNetworkAccessManager *manager;
    void buildGUI();
    QString help_text();

signals:

public slots:
    void getUpdate();
    void showWordsTable();
    void replyFinished(QNetworkReply *reply);
};

#endif // ABOUT_H
