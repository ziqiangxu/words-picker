#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
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
#include <QCloseEvent>
#include "systemtrayicon.h"
#include "windows/hyaline_window.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "windows/settings_window.h"
#include <QTimer>
//#include <tesseract/baseapi.h>

//using namespace tesseract;
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QLineEdit *input;

    QPushButton *query_button, *exchange_language, *about, *test_button;
    //QPushButton *derive;
    QComboBox *src_language, *des_language;
    QTextBrowser *browser;
    QClipboard *clipboard;
    Float_Button *float_button;
    Float_Browser *float_browser;
    Hyaline_Window *hyaline_window;
    About *about_window;
    QString src_word;
    QString des_word;
    // 查询单词的请求者
    // Requestor of the query
    enum Requestor {Mainwindow, Float_button, Float_browser, ocr} who_query;
    YoudaoAPI *youdao_api;
    SQLite sqlite;
    void query();
    void showResult();
    int button_time;
    void showAbout();
    //void derive_words();
    SystemTrayIcon *tray_icon;
    //TessBaseAPI *ocr_ins;

private:
    void buildGui();
    void initLanguage();
    void signalsAndSlots();
    bool recognizeImage();
    bool clipboard_flag;
    QPushButton *settings_button;
    QHBoxLayout *layout_root;
    QVBoxLayout *layout_view, *layout_button;
    SettingsWindow *settings_window;

    // 定时器用于input内容被修改后，延迟进行自动查询
    // Timer for auto query once the content in the "input" changed
    QTimer *timer;

private slots:
    void getResult(QByteArray re);
    void closeEvent(QCloseEvent *event);
    void trayIconActived(QSystemTrayIcon::ActivationReason reason);
    void getImageFromClipboard();

public slots:
    void hideFloat();
    void timerEvent(QTimerEvent *event);
    void queryInput();
    void onButtonReleased(int x, int y);
};

#endif // MAINWINDOW_H
