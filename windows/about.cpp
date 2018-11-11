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

About::About(QWidget *parent) : QMainWindow(parent)
{
    word_table = nullptr;
    buildGUI();
    connect(update, &QPushButton::clicked,
            this, &About::get_update);
    connect(derive, &QPushButton::clicked,
            this, &About::manage_new);
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
     move(100,100);
     setFixedSize(400,270);
     help = new QTextBrowser(this);
     help->setGeometry(0,0,400,270);
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

 void About::get_update()
 {
     QUrl url("https://github.com/ziqiangxu/freedict");
     QDesktopServices::openUrl(url);
 }

 void About::manage_new()
 {
     word_table = new Word_table;
     setVisible(false);
 }

 QString About::help_text()
 {
     QString content;
     content =
             "应用版本：53\n\n\
特别鸣谢:有道词典、谷歌翻译、Deepin\n\
       本应用组合了有道翻译API和谷歌网页翻译，本应用主要在Deepin平台下开发。\n\n\
OCR取词使用方法：\n\
       以Deepin为例，Ctrl+Alt+A启动截图程序，选中要识别翻译的区域，然后Ctrl+C将截图保存在剪切板中。\n\n\
主页：https://github.com/ziqiangxu/freedict/blob/master/README.md\n\n\
bug反馈：https://github.com/ziqiangxu/freedict/issues/new\n\
E-mail：ziqiang_xu@yeah.net";
     return content;
 }
