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
#include "float_button.h"
#include <QPainter>
#include <QMouseEvent>

Float_Button::Float_Button()
{
    setFixedSize(30,30);
    //setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);

    /*Test area*/
    qDebug("float_button");
}

void Float_Button::mousePressEvent(QMouseEvent *event)
{
    qDebug("Rceived a mouse event");
    if (event->button() == Qt::LeftButton)
    {
        emit clicked();
        qDebug("emit the click signal of Float_Button");
        this->hide();
    }
}


void Float_Button::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(rect(), QImage(":image/src/tran.png"));
}

bool Float_Button::isMouseOn()
{
    int cursor_x = QCursor::pos().x();
    int cursor_y = QCursor::pos().y();
    if (cursor_x > x() && cursor_x < (x() + width()) &&
            cursor_y > y() && cursor_y <(y() + height()))
        return true;
    return false;
}
