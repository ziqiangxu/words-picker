#include "youdaoapi.h"
#include <QtNetwork>
#include <QObject>
#include <QMessageBox>
#include <QDebug>

YoudaoAPI::YoudaoAPI()
{
}

void YoudaoAPI::translate(QString query, QString from,
                    QString to, QString appKey,
                    QString key)
{
    QString salt = QString(Randon());
    QString url = "http://openapi.youdao.com/api?";
    url.append("q=" + query);
    url.append("&from=" + from);
    url.append("&to=" + to);
    url.append("&appKey=" + appKey);
    url.append("&salt=" + salt);
    url.append("&sign=" + MD5(appKey + query + salt + key));
    qDebug() << "the request URL:" << url;
    request(url);  //Cause block when a wrong URL give
}

void YoudaoAPI::request(QString url)
{
    QNetworkAccessManager *manager;
    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished,
            this, &YoudaoAPI::reply);

    manager->get(QNetworkRequest(QUrl(url)));


    qDebug("YoudaoAPI::request");

}

void YoudaoAPI::reply(QNetworkReply *re)
{
    QByteArray result = re->readAll();
    emit finish(result);
}

QString YoudaoAPI::MD5(QString src)
{
    QString md5;
    QByteArray ba,bb;
    QCryptographicHash md(QCryptographicHash::Md5);
    ba.append(src);
    md.addData(ba);
    bb = md.result();
    md5.append(bb.toHex());
    qDebug() << "the MD5:" << md5;
    return md5;
}

int YoudaoAPI::Randon()
{
    int salt = qrand() % 10;
    qDebug() << "randon number--salt:" << salt;
    return salt;
}
