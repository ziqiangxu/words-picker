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
#include "about.h"
#include "../SQL/sqlite.h"
#include "QDesktopServices"
#include <QTableView>
#include <QStandardItemModel>
#include <QDebug>

About::About(QWidget *parent) : QWidget(parent)
{
    word_table = nullptr; 
    info = new QSettings(":/resources/info", QSettings::IniFormat);
//    qDebug() << info->value("version/main").toString();
    version_main = info->value("version/main").toInt();
    version_subordinate = info->value("version/subordinate").toInt();
    buildGUI();
    connect(update, &QPushButton::clicked,
            this, &About::getUpdate);
    connect(derive, &QPushButton::clicked,
            this, &About::showWordsTable);
}

About::~About()
{
    delete help;
    delete derive;
    delete update;
    delete word_table;
}

 void About::buildGUI()
 {
     setWindowTitle(tr("关于"));
     setWindowFlags(Qt::WindowStaysOnTopHint);
     int pos_x = QCursor::pos().x();
     int pos_y = QCursor::pos().y();
     move(pos_x - 30, pos_y - 30);
     setFixedSize(400,270);
     help = new QTextBrowser(this);
     help->setGeometry(0, 0, 400, 270);
     help->setText(help_text());

     derive = new QPushButton(this);
     derive->setText(tr("单词本"));
     derive->move(220,10);
     derive->adjustSize();

     update = new QPushButton(this);
     update->move(310,10);
     update->setText(tr("获取更新"));
     update->adjustSize();
 }

 void About::getUpdate()
 {
     /* 从github下载文件，然后进行和本地版本进行比较
     *  https://raw.githubusercontent.com/ziqiangxu/words-picker/master/deb/
     *  freedict/DEBIAN/control */
     manager = new QNetworkAccessManager(this);
     QNetworkRequest request = QNetworkRequest(
                 QUrl("https://raw.githubusercontent.com/ziqiangxu/words-picker/"
                      "master/resources/info")
                 );
//     QNetworkRequest request = QNetworkRequest(
//                 QUrl("https://blog.csdn.net/GoForwardToStep/article/details/53588961")
//                 );

//     QSslConfiguration config = request.sslConfiguration();
//     config.setPeerVerifyMode(QSslSocket::VerifyNone);
//     config.setProtocol(QSsl::AnyProtocol);
//     config.setProtocol(QSsl::TlsV1SslV3);
//     request.setSslConfiguration(config);

     qDebug() << "version:" << QSslSocket::sslLibraryVersionString();
     qDebug() << QSslSocket::sslLibraryBuildVersionNumber();

     connect(manager, &QNetworkAccessManager::finished,
             this, &About::replyFinished);
     manager->get(request);
 }

 void About::replyFinished(QNetworkReply *reply)
 {
     QString res = reply->readAll();
     qDebug() << "res:" << res;

     if(res.isEmpty()) {
         QMessageBox::warning(this, tr("检查更新失败"), tr("检查更新失败，可能是网络问题，重试一下吧"));
         return;
     }
     QFile outFile("/opt/freedict/info");
     outFile.open(QIODevice::WriteOnly | QIODevice::WriteOnly);
     QTextStream in(&outFile);
     in << res;

     info_ = new QSettings("/opt/freedict/info", QSettings::IniFormat);

     int version_main_ = info_->value("version/main").toInt();
     int version_subordinate_ = info_->value("version/subordinate").toInt();

     // 如果主版本号或者次版本号大于本版本，则直接打开浏览器跳转到下载页面
     if (version_main_ > version_main | version_subordinate_ > version_subordinate){
         QUrl url("https://github.com/ziqiangxu/words-picker/releases");
         QDesktopServices::openUrl(url);
     } else {
         QMessageBox::information(this, tr("检查更新"), tr("您这已经是最新版本了"));
     }
 }

 void About::showWordsTable()
 {
     word_table = new Word_table;
     this->setVisible(false);
 }

 QString About::help_text()
 {
     QString content;
     content.sprintf(
             "应用版本：%d.%d\n\n\
特别鸣谢:有道词典、谷歌翻译、Deepin\n\
       本应用组合了有道翻译API和谷歌网页翻译，本应用主要在Deepin平台下开发。\n\n\
OCR取词使用方法：\n\
       以Deepin为例，Ctrl+Alt+A启动截图程序，选中要识别翻译的区域，然后Ctrl+C将截图保存在剪切板中。\n\n\
主页：https://github.com/ziqiangxu/words-picker/blob/master/README.md\n\n\
bug反馈：https://github.com/ziqiangxu/words-picker/issues/new\n\
E-mail：ziqiang_xu@yeah.net", version_main, version_subordinate);
     return content;
 }
