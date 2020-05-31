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
#include "mainwindow.h"
#include <QApplication>
#include "event/eventmonitor.h"
#include "defined.h"
#include <QFile>

void setStyle(QApplication *app)
{
//    从资源文件读取样式
    QFile qss(":/qss/resources/light.qss");
    qss.open(QFile::ReadOnly);
    app->setStyleSheet(qss.readAll());
    qss.close();
}


bool createDirectories () {
    // to store some temporary files
    // QString workPathName = APP_NAME + "_xu";
    QString workPathName = APP_NAME;
    QDir tmpDir = QDir(SYSTEM_TMP_PATH);
    if (!tmpDir.mkpath(workPathName)) return false;
    return true;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 设置样式
    setStyle(&app);

    // create directory
    if (createDirectories() == false)
        return 0;

    MainWindow w;

    /*
    QObject::connect(
        &event_monitor,
        &EventMonitor::buttonPress,
        w.browser,
        [=] (int x, int y) {
            DEBUG << (QString("Button press (%1, %2)").arg(x).arg(y));
        },
        Qt::QueuedConnection);
    QObject::connect(
        &event_monitor,
        &EventMonitor::buttonDrag,
        w.browser,
        [=] (int x, int y) {
            DEBUG << (QString("Button drag (%1, %2)").arg(x).arg(y));
        },
        Qt::QueuedConnection);
    QObject::connect(
        &event_monitor,
        &EventMonitor::buttonRelease,
        w.browser,
        [=] (int x, int y) {
            DEBUG << (QString("Button release (%1, %2)").arg(x).arg(y));
        },
        Qt::QueuedConnection);
    QObject::connect(
        &event_monitor,
        &EventMonitor::keyPress,
        w.browser,
        [=] (int code) {
            DEBUG << (QString("Key press %1").arg(code));
        },
        Qt::QueuedConnection);
    QObject::connect(
        &event_monitor,
        &EventMonitor::keyRelease,
        w.float_browser,
        [=] (int code) {
            DEBUG << (QString("Key release %1").arg(code));
        },
        Qt::QueuedConnection);
    //*/
    //开发时显示主窗口
#if IS_DEV
    w.show();
#endif

    return app.exec();
}
