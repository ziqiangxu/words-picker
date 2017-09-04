#include "mainwindow.h"
#include <QApplication>
#include "event/eventmonitor.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    EventMonitor event_monitor;
    event_monitor.start();
    QObject::connect(&event_monitor, &EventMonitor::EscPressed,
                     &w, &MainWindow::hide_float);
    QObject::connect(&event_monitor, &EventMonitor::buttonPress,
                     &w,&MainWindow::hide_float);
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

    return a.exec();
}
