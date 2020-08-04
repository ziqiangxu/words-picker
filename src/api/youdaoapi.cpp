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
#include "../defined.h"

YoudaoAPI::YoudaoAPI()
{
}

void YoudaoAPI::translate_old(QString query, QString from,
                    QString to, QString appKey,
                    QString key)
{
    // todo 在这里判断是单词还是多词，分别进行查询
//    QString salt = QString(Randon());
    QString salt = "s";
    QString url = "https://openapi.youdao.com/api?";
    QString query_encoded = QUrl::toPercentEncoding(query);
    url.append("q=" + query_encoded)
            .append("&from=" + from)
            .append("&to=" + to)
            .append("&appKey=" + appKey)
            .append("&salt=" + salt)
            .append("&sign=" + MD5(appKey + query + salt + key));
    this->query_url = QUrl(url);
    INFO << "Url before encode:" << url;
    INFO << "Encode URL:" << endl << this->query_url.toEncoded();
    request();  //Cause block when a wrong URL give
}

void YoudaoAPI::translate(QString query, QString from, QString to)
{
    // 处理pdf换行单词被打断的问题
    query.replace("-\n", "");

    query = query.simplified();
    QString query_encode = QUrl::toPercentEncoding(query);
    QString query_url;

    query_url = BASE_URL + "/translate?";

    query_url.append("q=" + query_encode)
            .append("&from=" + from)
            .append("&to=" + to);
    INFO << "Encoded url: " << query_url;
    this->query_url = query_url;
    request();
}

void YoudaoAPI::request()
{
    QNetworkAccessManager *manager;
    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished,
            this, &YoudaoAPI::reply);

    manager->get(QNetworkRequest(this->query_url));

}

void YoudaoAPI::reply(QNetworkReply *re)
{
    QByteArray res = re->readAll();
    if (res.isEmpty() && this->query_count < 3)
    {
        INFO << this->query_count << " times retry";
        this->query_count++;
        this->request();
        return;
    }
    this->query_count = 0;
    // 创建一个Result实例，它将解析res中的数据
    result = new Result(res);
    emit finish();
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
    INFO << "the MD5:" << md5;
    return md5;
}

int YoudaoAPI::Randon()
{
    int salt = qrand() % 10;
    INFO << "randon number--salt:" << salt;
    return salt;
}
