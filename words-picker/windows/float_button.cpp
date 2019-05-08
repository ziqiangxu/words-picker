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
#include "float_button.h"
#include <QPainter>
#include <QMouseEvent>
#include "../defined.h"

FloatButton::FloatButton()
{
    setFixedSize(30, 30);
    // 设置窗口透明
    setAttribute(Qt::WA_TranslucentBackground, true);
    // 设置无边框, 以及不获得焦点
    setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);

    /*Test area*/
    INFO << "build float_button";
}

void FloatButton::mousePressEvent(QMouseEvent *event)
{
//    重写窗口鼠标按下事件
    INFO << "Rceived a mouse event";
    if (event->button() == Qt::LeftButton)
    {
        emit clicked();
        INFO << "flout_btton clicked";
        this->hide();
    }
}


void FloatButton::paintEvent(QPaintEvent *)
{
//    绘制图标
    QPainter painter(this);
    painter.drawImage(rect(), QImage(":/image/resources/words-picker.png"));
}

bool FloatButton::isMouseOn()
{
//    检查鼠标是否悬浮按钮区域
    int cursor_x = QCursor::pos().x();
    int cursor_y = QCursor::pos().y();
    if (cursor_x > x() && cursor_x < (x() + width()) &&
            cursor_y > y() && cursor_y <(y() + height()))
        return true;
    return false;
}
