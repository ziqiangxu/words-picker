#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H
#include <QSystemTrayIcon>
#include <QMainWindow>
#include <QIcon>
#include <QMenu>
#include <QAction>
#include <QObject>

class SystemTrayIcon: public QSystemTrayIcon
{
    //Q_OBJECT
public:
    explicit SystemTrayIcon(QObject *parent=nullptr);
    QAction *action_quit;
private:
    QMenu *menu;
    void build_menu();
    void connect_menu_action();
};

#endif // SYSTEMTRAYICON_H
