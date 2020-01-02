#ifndef YOUDAOAPI_H
#define YOUDAOAPI_H

#include <QObject>
#include <QNetworkReply>
#include <QUrl>
#include "result.h"

class YoudaoAPI:public QObject
{
    Q_OBJECT
public:
    YoudaoAPI();
    void translate_old(QString query = "deepin",
                      QString from = "EN",
                      QString to = "zh_CHS",
                      QString appKey = "179b7fabf47afb85",
                      QString key = "ndTLw0HSgoUhkpgP0jGK7ynUI1KHFwcd");
    void translate(QString query, QString from, QString to);
    void request();
    Result *result;

private:
    QString MD5(QString src);
    int Randon();
    QUrl query_url;
    int query_count;
    QString translation;

signals:
    void finish();

private slots:
    void reply(QNetworkReply *);
};

#endif // YOUDAOAPI_H
