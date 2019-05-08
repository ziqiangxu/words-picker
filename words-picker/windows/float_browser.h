/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright   2017 ~ Now Ziqiang Xu
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
#ifndef FLOUT_BROWSER_H
#define FLOUT_BROWSER_H
#include <QMainWindow>
#include <QLineEdit>
#include <QTextBrowser>
#include <QPushButton>
#include <QCloseEvent>

class FloatBrowser : public QMainWindow
{
public:
    FloatBrowser();
    ~FloatBrowser();
    QTextBrowser *browser;
    QPushButton *google_translate;
    QPushButton *query;
    QPushButton *add_new;
    QLineEdit *input;
    bool isMouseOn();
    void google_web_translate(QString src_word,
                              QString src_language = "en",
                              QString des_language = "zh-CN");
protected:
private slots:
    void closeEvent(QCloseEvent *event);

signals:
    void add_new_word();

};

#endif // FLOUT_BROWSER_H
