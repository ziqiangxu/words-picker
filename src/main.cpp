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

#if defined Q_OS_LINUX  // Just for Linux
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

QString getCurrentUserNameLinux()
{
	QProcess process(nullptr);
	process.setProgram("whoami");
	process.start();
	while (process.state() != QProcess::NotRunning)
		qApp->processEvents();
	return process.readAll();
}

bool check_only()
{
    // Get current user name
    QString userName = getCurrentUserNameLinux();
    DEBUG << "user name:" << userName;
//    创建文件锁
    QString lockFilePath = "/tmp/lockfile_for_" + userName;
    QByteArray ba = lockFilePath.toLatin1();
    const char filename[] = ba.data();
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
    QFile qss(":/qss/resources/light.qss");
    qss.open(QFile::ReadOnly);
    app->setStyleSheet(qss.readAll());
    qss.close();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

#if defined Q_OS_LINUX
    if (check_only() == false)
        return 0;
#endif

    // 设置样式
    setStyle(&app);
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
