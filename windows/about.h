#ifndef ABOUT_H
#define ABOUT_H

#include <DMainWindow>
#include <QTextBrowser>
#include <dpushbutton.h>
#include "word_table.h"
DWIDGET_USE_NAMESPACE
class About : public DMainWindow
{
    Q_OBJECT
public:
    explicit About(QWidget *parent = nullptr);
    ~About();

    QTextBrowser *help;
    DPushButton *derive;
    DPushButton *update;
    Word_table *word_table;

signals:

public slots:
    void get_update();
    void manage_new();
private:
    void buildGUI();
    QString help_text();
};

#endif // ABOUT_H
