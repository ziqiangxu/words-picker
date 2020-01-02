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
#ifndef FLOAT_BUTTON_H
#define FLOAT_BUTTON_H

#include <QPainter>
#include <QWidget>
#include <QPushButton>

class FloatButton : public QWidget
{
    Q_OBJECT
public:
    FloatButton();
    QPainter painter;
    bool isMouseOn();

private:

protected:
    void mousePressEvent(QMouseEvent *);

signals:
    void pressed();

protected:
    void paintEvent(QPaintEvent *);
};

#endif // FLOAT_BUTTON_H
