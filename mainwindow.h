#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QTextBrowser>
#include "api/youdaoapi.h"
#include "windows/float_browser.h"
#include "windows/float_button.h"
#include <qclipboard.h>
#include "SQL/sqlite.h"
#include <windows/about.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QLineEdit *input;
    QPushButton *exchange_language;
    QPushButton *about;
    QPushButton *derive;
    QComboBox *src_language;
    QComboBox *des_language;
    QTextBrowser *browser;
    QClipboard *clipboard;
    Float_Button *float_button;
    Float_Browser *float_browser;
    About *about_window;
    QString src_word;
    QString des_word;
    enum Requestor {Mainwindow, Float_button, Float_browser} who_query;
    YoudaoAPI *youdao_api;
    SQLite sqlite;
    void query();
    void show_result();
    int button_time;
    void show_about();
    void derive_words();
private:
    void build_GUI();
    void init_language();
    void signals_slots();
private slots:
    void get_result(QByteArray re);
public slots:
    void hide_float();
    void timerEvent(QTimerEvent *event);
};

#endif // MAINWINDOW_H
