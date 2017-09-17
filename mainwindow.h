#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <dpushbutton.h>
#include <dlineedit.h>
#include <QComboBox>
#include <QTextBrowser>
#include "api/youdaoapi.h"
#include "windows/float_browser.h"
#include "windows/float_button.h"
#include <qclipboard.h>
#include "SQL/sqlite.h"
#include <windows/about.h>

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    DLineEdit *input;
    DPushButton *exchange_language;
    DPushButton *about;
    DPushButton *derive;
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
