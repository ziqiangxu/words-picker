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
#include "float_browser.h"
#include <QFocusEvent>
#include <QApplication>
#include <QClipboard>
#include <QDebug>
#include <QDesktopServices>

Float_Browser::Float_Browser()
{
    setWindowTitle(tr("快速查词"));
    setFixedSize(280,300);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::WindowCloseButtonHint);

    input = new QLineEdit(this);
    input->setGeometry(0,0,190,30);

    browser = new QTextBrowser(this);
    browser->setGeometry(0,40,280,260);
    qDebug("Float_browser object creating");
    qDebug() << browser->size();


    add_new = new QPushButton(this);
    add_new->move(195,40);
    add_new->setText(tr("加入生词"));
    add_new->adjustSize();

    query = new QPushButton(this);
    query->move(195,0);
    query->setText(tr("查询"));
    query->setFixedSize(add_new->size());

    google_translate = new QPushButton(this);
    google_translate->move(195,80);
    google_translate->setText(tr("Google翻译"));
    google_translate->setFixedSize(add_new->size());
}

Float_Browser::~Float_Browser()
{
    delete input;
    delete browser;
    delete google_translate;
    delete query;
    delete add_new;
}

bool Float_Browser::isMouseOn()
{
    int cursor_x = QCursor::pos().x();
    int cursor_y = QCursor::pos().y();
    if (cursor_x > x() && cursor_x < (x() + width()) &&
            cursor_y > y() && cursor_y <(y() + height()))
        return true;
    return false;
}

void Float_Browser::google_web_translate(QString src_word,
                                         QString src_language,
                                         QString des_language)
{
    if (src_language == "zh_CHS"){
        src_language = "zh-CN";
    }
    if (des_language == "zh_CHS"){
        des_language == "zh-cn";
    }
    qDebug() << "源语言：" << src_language << "\n目标语言：" << des_language;
    QUrl google_url(tr("https://translate.google.cn/#%1/%2/%3")
                    .arg(src_language)
                    .arg(des_language)
                    .arg(src_word));
    QDesktopServices::openUrl(google_url);
}
