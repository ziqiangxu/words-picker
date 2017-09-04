#ifndef EVENTMONITOR_H
#define EVENTMONITOR_H

#include <QThread>
#include <X11/Xlib.h>
#include <X11/extensions/record.h>

// Virtual button codes that are not defined by X11.
#define Button1			1
#define Button2			2
#define Button3			3
#define WheelUp			4
#define WheelDown		5
#define WheelLeft		6
#define WheelRight		7
#define XButton1		8
#define XButton2		9

class EventMonitor : public QThread
{
    Q_OBJECT

public:
    EventMonitor(QObject *parent = 0);

signals:
    void buttonPress(int x, int y);
    void buttonDrag(int x, int y);
    void buttonRelease(int x, int y);
    void keyPress(int code);
    void keyRelease(int code);
    void EscPressed();

protected:
    bool filterWheelEvent(int detail);
    static void callback(XPointer trash, XRecordInterceptData* data);
    void handleRecordEvent(XRecordInterceptData *);
    void run();

private:
    bool isPress;
};


#endif // EVENTMONITOR_H
