#include "systemtrayicon.h"

SystemTrayIcon::SystemTrayIcon(QObject *parent):QSystemTrayIcon(parent)
{
    QIcon icon = QIcon(":image/resources/words-picker.png");
    setToolTip(QString("words-picker"));
    setIcon(icon);
    build_menu();
}

void SystemTrayIcon::build_menu()
{
    menu = new QMenu();
    action_quit = new QAction(this);
    action_quit->setText("退出");
    menu->addAction(action_quit);

    connect_menu_action();
    setContextMenu(menu);
}

void SystemTrayIcon::connect_menu_action()
{
}
