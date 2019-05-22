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
#include <QDesktopServices>
#include "../defined.h"

FloatBrowser::FloatBrowser()
{
    setWindowTitle(tr("快速查词"));
    setFixedSize(280,300);
    setWindowFlags(Qt::WindowStaysOnTopHint |
                   Qt::WindowCloseButtonHint |
                   Qt::Tool);

    input = new QLineEdit(this);
    input->setGeometry(0,0,190,30);

    browser = new QTextBrowser(this);
    browser->setGeometry(0,30,280,240);
    INFO << "Float_browser object creating" << browser->size();

    query = new QPushButton(this);
    query->setGeometry(195, 0, 80, 30);
    query->setText(tr("查询"));

//    add_new = new QPushButton(this);
//    add_new->setGeometry(5, 270, 80, 30);
//    add_new->setText(tr("加入生词"));
//    add_new->adjustSize();

    google_translate = new QPushButton(this);
    google_translate->setGeometry(100, 270, 80, 30);
    google_translate->setText(tr("Google翻译"));
}

FloatBrowser::~FloatBrowser()
{
    delete input;
    delete browser;
    delete google_translate;
    delete query;
//    delete add_new;
}

bool FloatBrowser::isMouseOn()
{
//    检查鼠标是否在窗口区域
    int cursor_x = QCursor::pos().x();
    int cursor_y = QCursor::pos().y();
    INFO << "pos_x:" << cursor_x << "pos_y:" << cursor_y;
    INFO << "x():" << x() << "y()" << y();
    INFO << "width:" <<width() << "height" << height();
    if (cursor_x > x() && cursor_x < (x() + width()) &&
            cursor_y > y() - 35 && cursor_y < (y() + height() + 35))
    {
        DEBUG << "Mouse on the browser";
        return true;
    }
    DEBUG << "Mouse out of the browser";
    return false;
}

void FloatBrowser::google_web_translate(QString src_word,
                                         QString src_language,
                                         QString des_language)
{
//    用浏览器打开google网页翻译
    // Visite google translation by browser
    INFO << "src_language:" << src_language << " des_language:" << des_language;
    if (src_language == "zh_CHS") src_language = "zh-CN";
    if (src_language == "EN") src_language = "en";
    if (des_language == "zh_CHS") des_language = "zh-CN";
    if (des_language == "EN") des_language = "en";

    INFO << "源语言：" << src_language << "\n目标语言：" << des_language;
    QUrl google_url(tr("https://translate.google.cn/#%1/%2/%3")
                    .arg(src_language)
                    .arg(des_language)
                    .arg(src_word));
    QDesktopServices::openUrl(google_url);
}

void FloatBrowser::closeEvent(QCloseEvent *event)
{
//    隐藏窗口而不是关闭窗口
    INFO << "hide the float window";
    this->hide();
    event->ignore();
}
