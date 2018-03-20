#ifndef ABOUT_H
#define ABOUT_H

#include <QMainWindow>
#include <QTextBrowser>
#include <QPushButton>
#include "word_table.h"
class About : public QMainWindow
{
    Q_OBJECT
public:
    explicit About(QWidget *parent = nullptr);
    ~About();

    QTextBrowser *help;
    QPushButton *derive;
    QPushButton *update;
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
