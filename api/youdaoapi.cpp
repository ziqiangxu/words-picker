/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright (C) Ziqiang Xu
 *
 * Author:     Ziqiang Xu <ziqiang_xu@yeah.net>
 * Maintainer: Ziqiang Xu <ziqiang_xu@yeah.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "youdaoapi.h"
#include <QtNetwork>
#include <QObject>
#include <QMessageBox>
#include <QDebug>
#include <QUrl>

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
    QUrl url_encode(url);
    qDebug() << "the request URL:" << url;
    request(url_encode.toString(QUrl::FullyEncoded));  //Cause block when a wrong URL give
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
