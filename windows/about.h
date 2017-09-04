#ifndef ABOUT_H
#define ABOUT_H

#include <DMainWindow>
#include <QTextBrowser>
#include <dpushbutton.h>
DWIDGET_USE_NAMESPACE
class About : public DMainWindow
{
    Q_OBJECT
public:
    explicit About(QWidget *parent = nullptr);

    QTextBrowser *help;
    DPushButton *derive;
    DPushButton *update;
    void derive_new();
signals:

public slots:
    void get_update();
private:
    void buildGUI();
    QString help_text();
};

#endif // ABOUT_H
