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
#include <QDebug>
#include <QFile>

#if defined Q_OS_LINUX
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
bool check_only()
{
//    创建文件锁
    const char filename[] = "/tmp/lockfile_for_freedict";
    int fd = open (filename, O_WRONLY | O_CREAT , 0644);
    int flock = lockf(fd, F_TLOCK, 0);
    if (fd == -1) {
        perror("open lockfile/n");
        return false;
    }
    if (flock == -1) {
        perror("lock file error/n");
        return false;
    }
    return true;
}
#endif

void setStyle(QApplication *app)
{
//    从资源文件读取样式
//    QFile qss("/home/xu/git/freedict/src/style.qss");
//    QFile qss(":/qss/resources/black.qss");
    QFile qss(":/qss/resources/light.qss");
    qss.open(QFile::ReadOnly);
//    qApp->setStyle(qss.readAll());
    app->setStyleSheet(qss.readAll());
    qss.close();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    if (check_only() == false)
        return 0;
    // 设置样式
    setStyle(&app);
    MainWindow w;
    EventMonitor event_monitor;
    event_monitor.start();
    QObject::connect(&event_monitor, &EventMonitor::buttonPress,
                     &w, &MainWindow::onButtonPressed);
    QObject::connect(&event_monitor, &EventMonitor::buttonRelease,
                     &w, &MainWindow::onButtonReleased);
    /*
    QObject::connect(
        &event_monitor,
        &EventMonitor::buttonPress,
        w.browser,
        [=] (int x, int y) {
            qDebug() << (QString("Button press (%1, %2)").arg(x).arg(y));
        },
        Qt::QueuedConnection);
    QObject::connect(
        &event_monitor,
        &EventMonitor::buttonDrag,
        w.browser,
        [=] (int x, int y) {
            qDebug() << (QString("Button drag (%1, %2)").arg(x).arg(y));
        },
        Qt::QueuedConnection);
    QObject::connect(
        &event_monitor,
        &EventMonitor::buttonRelease,
        w.browser,
        [=] (int x, int y) {
            qDebug() << (QString("Button release (%1, %2)").arg(x).arg(y));
        },
        Qt::QueuedConnection);
    QObject::connect(
        &event_monitor,
        &EventMonitor::keyPress,
        w.browser,
        [=] (int code) {
            qDebug() << (QString("Key press %1").arg(code));
        },
        Qt::QueuedConnection);
    QObject::connect(
        &event_monitor,
        &EventMonitor::keyRelease,
        w.float_browser,
        [=] (int code) {
            qDebug() << (QString("Key release %1").arg(code));
        },
        Qt::QueuedConnection);
    //*/
    w.show();

    return app.exec();
}

