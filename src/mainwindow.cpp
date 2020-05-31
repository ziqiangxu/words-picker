/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright (C) Ziqiang Xu
 *
 * Author:     Ziqiang Xu <ziqiang_xu@yeah.net>
 * Maintainer: Ziqiang Xu <ziqiang_xu@yeah.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "mainwindow.h"
#include "defined.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QApplication>
#include <QMessageBox>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include "api/result.h"

//using namespace tesseract;
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    //init the variates
    settings_window = new SettingsWindow();
    clipboard = QApplication::clipboard();
    youdao_api = new YoudaoAPI();
    picker = new Picker();
//    sqlite = SQLite();
    clipboard_flag = true;
    is_selection_changed = false;
    isButtonPressed = false;
    timer = new QTimer();

    buildGui();
    eventsMonit();
    //ocr_ins = new tesseract::TessBaseAPI();
    signalsAndSlots();
    //*Test area
    //setStyleSheet("background-color:blue");
    //*/
}

MainWindow::~MainWindow()
{
}

/**
 * @brief MainWindow::eventsMonit
 * monit the mouse and keyborad events
 */
void MainWindow::eventsMonit()
{
    this->event_monitor = new EventMonitor();
     event_monitor->start();
     connect(event_monitor, &EventMonitor::buttonPress,
                      this, &MainWindow::onButtonPressed);
     connect(event_monitor, &EventMonitor::buttonRelease,
                      this, &MainWindow::onButtonReleased);
}

void MainWindow::closeEvent(QCloseEvent *event){
    // 点击关闭的时候，收起到系统托盘
    // When the close button clicked, fold up to system tray
    this->hide();
    event->ignore();
}

// 构建GUI Build the GUI
void MainWindow::buildGui()
{
    setWindowTitle(APP_NAME);
    move(100, 100);
    setFixedSize(400, 254);

    //Layout
    layout_root = new QHBoxLayout(this);
    layout_root->setMargin(1);
    layout_view = new QVBoxLayout;
    layout_root->addLayout(layout_view);
    layout_button = new QVBoxLayout;
    layout_root->addLayout(layout_button);

    input = new QLineEdit();
    input->setText(clipboard->text());
    input->selectAll();
    layout_view->addWidget(input);

    browser = new QTextBrowser();
    layout_view->addWidget(browser);

    query_button = new QPushButton(this);
    query_button->setText(tr("查询\b"));
    layout_button->addWidget(query_button);

    src_language = new QComboBox(this);
    layout_button->addWidget(src_language);

    exchange_language = new QPushButton(this);
    exchange_language->setText(tr("交换语言"));
    exchange_language->adjustSize();
    layout_button->addWidget(exchange_language);

    des_language = new QComboBox(this);
    initLanguage();
    layout_button->addWidget(des_language);

    settings_button = new QPushButton(tr("设置"));
    layout_button->addWidget(settings_button);

    /*
    derive = new QPushButton(this);
    derive->setText(tr("导出生词"));
    layout_button->addWidget(derive);
    */

    about = new QPushButton(this);
    about->setText(tr("更多"));
    layout_button->addWidget(about);

    // 测试的东西
    // Just for test
    test_button = new QPushButton(this);
    test_button->setText("测试");
    test_button->hide();

    float_button = new FloatButton();
    float_browser = new FloatBrowser();

    hyaline_window = new HyalineWindow();


    about_window = new About;
    about_window->getUpdate();

    tray_icon = new SystemTrayIcon(this);
    tray_icon->show();
    //*Test area
    //setWindowFlags(Qt::WindowStaysOnTopHint);
    //*/
}

// 初始化支持的语言列表 Init the supported language
void MainWindow::initLanguage()
{
    QStringList language;
    language << "EN" << "zh_CHS" << "ja" << "ko" << "fr" << "ru"
         << "pt" << "es";
    src_language->addItems(language);
    des_language->addItems(language);
    src_language->setCurrentIndex(0);
    des_language->setCurrentIndex(1);
}

// 连接信号和槽 Connect signals and slots
void MainWindow::signalsAndSlots()
{
    //测试按钮的点击事件
    connect(test_button, &QPushButton::clicked,
            this, [=]{

    });

    // 系统托盘事件处理
    // Deal with the tray event
//    connect(tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
//            this, SLOT(trayIconActived(QSystemTrayIcon::ActivationReason))
//            );
    connect(tray_icon, &QSystemTrayIcon::activated,
            this, &MainWindow::trayIconActived);

    // 选择退出菜单
    // quit the application
    connect(tray_icon->action_quit,&QAction::triggered,
            this, [=]{
        INFO << "Received the signal of tray_icon，quit the application";
        qApp->quit();
    });

    // 有道api返回结果后获取内容
    // Get result after youdao api response
    connect(youdao_api, &YoudaoAPI::finish,
            this, &MainWindow::onReplyGot);

//------Response the "mainwindow"
    // 按下Enter进行查询
    // Query when "Enter" pressed in "input"
    connect(input, &QLineEdit::returnPressed,
            this, [=] {
        queryInput();
        this->input->selectAll();
    });

    // 按下窗口的按钮查询
    // Query when query_button clicked
    connect(query_button, &QPushButton::clicked,
            this, [=] {
        queryInput();
        this->input->selectAll();
    });

    // 时间到即查询,然后停止计时器，这种情况不要全选文本
    // query once timeout, and stop the timer, do not select all text
    connect(timer, &QTimer::timeout,
            this, [=] {
        queryInput();
//        int l = input->text().length();
//        input->setCursorPosition(l);
        timer->stop();
    });

    // input文本改变之后，启动定时器，将延迟0.5秒自动查询内容
    // start timer once content in "input" changed，auto query delay 0.5 seconds
    connect(input, &QLineEdit::textChanged,
            this, [=] {
        timer->start(500);
    });

    // 语言发生变化后让input获得焦点
    // "input" get focus when language changed
    connect(exchange_language,&QPushButton::clicked,
            this, [=]{
        int int_temp = src_language->currentIndex();
        src_language->setCurrentIndex(des_language->currentIndex());
        des_language->setCurrentIndex(int_temp);
        queryInput();
        input->selectAll();
    });

    /* 注意，activated信号在QComBox这个类中被重载了。要使用函数指针的语法来连接，你必须在
     * 静态强制转换中指定信号类型 */
    /*Note: Signal activated is overloaded in this class. To connect to this one
     * using the function pointer syntax, you must specify the signal type in a
     * static cast */
    connect(src_language, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated),
            this,[=]{input->setFocus();});
    connect(des_language, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated),
            this, [=]{input->setFocus();});

    // 从剪切板获取图像
    // Get the image from the clipboard
    connect(clipboard, &QClipboard::dataChanged,
            this, &MainWindow::getImageFromClipboard);

//------Response the "float_button"
    // 文本被选中的时候显示悬浮按钮，但它不是一个按钮，实际上是一个悬浮的窗口。5s后自动消失
    //Show "float_button" when the selected text changed,it's not a button but a window in fact
//    connect(clipboard, &QClipboard::selectionChanged,
//            float_button, [=]{
//        /* 主要是在chrome浏览器中鼠标未释放就会弹出悬浮按钮
//         * 如果鼠标处于按下状态，直接返回 */
//        this->is_selection_changed = true;
//        this->src_word = this->clipboard->text(QClipboard::Selection);
//        INFO << "selection changed!";
//        if (this->isButtonPressed) return;
//        this->is_selection_changed = false;
//        // 根据翻译模式查询
//        this->queryByMode();
//    });
    connect(picker, &Picker::wordsPicked,
            this, &MainWindow::onWordsPicked);

    //Show "float_browser" after clicked the "float_button"
    connect(float_button, &FloatButton::pressed,
            this, &MainWindow::onFloatButtonClicked);

//------Response the "float_browser"
    connect(float_browser->input, &QLineEdit::returnPressed,
            this, [=]{
        src_word = float_browser->input->text();
        who_query = Requestor::FloatBrowserE;
        query();
        float_browser->browser->setText(tr("正在查询"));
        float_browser->input->selectAll();
    });

    connect(float_browser->btn_query, &QPushButton::clicked,
            this, [=]{
        src_word = float_browser->input->text();
        who_query = Requestor::FloatBrowserE;
        query();
        float_browser->browser->setText(tr("正在查询"));
        float_browser->input->selectAll();
    });

//    connect(float_browser->add_new, &QPushButton::clicked,
//            this, [=]{
//        QString sql("UPDATE history SET sort='new' WHERE word='");
//        sql += src_word + "'";
//        sqlite.exec(sql);
//    });

    connect(float_browser->google_translate, &QPushButton::clicked,
            this, [=]{
        INFO << src_language->currentText() << des_language->currentText();
        src_word = float_browser->input->text();
        float_browser->google_web_translate(src_word,
                                            src_language->currentText(),
                                            des_language->currentText());
    });

//------Response the "about"
    connect(about, &QPushButton::clicked,
            this, &MainWindow::showAbout);

//------Response the "setting"
    connect(settings_button, &QPushButton::clicked,
            this, [=]{
        settings_window->show_options();
    });
}

void MainWindow::queryByMode()
{
    // 自动翻译选项
    if (settings_window->setting_map->find("is_auto_translate").value() == "true")
    {
        // 相当于点击了一下悬浮按钮，直接弹出悬浮窗口
        float_button->pressed(); return;
    }
    // 不开启对选中文本的翻译
    if (settings_window->setting_map->find("is_selected").value() == "false") return;

    float_button->setVisible(true);
    float_button->move(QCursor::pos().x() + 5, QCursor::pos().y() + 5);
    button_time = startTimer(5000);
}

void MainWindow::getImageFromClipboard()
{
    // 从剪切板获取图像
    // Get image from clipboard
    if (settings_window->setting_map->find("is_ocr").value() == "false")
    {
        return;
    }
    INFO << "Clipboard changed";
    QImage image = clipboard->image(QClipboard::Clipboard);
    if (image.isNull())
    {
        INFO << "Image not exist!";
    } else {
        if(clipboard_flag)
        {
            //Show the flout_browser right now
            float_browser->browser->setText(tr("正在查询"));
            float_browser->move(QCursor::pos());
            float_browser->setVisible(true);
            clipboard_flag = false;

            int height = image.height();
            int width = image.width();
            INFO << "Width of image:" << width << "Height of image:" << height;
            if (height < 30)
            {
                //The image is too small, need to be enlarged.
                float scale = 50 / height;
                //image = image.scaled(width*3, height*3, Qt::KeepAspectRatio);
                image = image.scaled(int(width*scale), 50, Qt::KeepAspectRatio);
            }

            image.save(OCR_IMG_PATH, "PNG", -1);
            INFO << "Image found!";
/*
 * in the file /usr/include/tesseract/baseapi.h
 * fuction TesseractRect will return the result
 */
            recognizeImage();
        } else {
            clipboard_flag = true;
        }
    }
}

void MainWindow::queryInput()
{
   /* 1. 获取要查询的文本
      2. 设置查询者为主窗口
      3. 进行查询 */
    if (this->input->text() == "") return;  // 空文本不查询
    this->src_word = this->input->text();
    this->who_query = this->Requestor::MainWindowE;
    this->query();
    browser->setText(tr("查询中"));
    INFO << "The sender is:" << sender();
}

// 对截取的图像进行识别 Recognize the scratched image
bool MainWindow::recognizeImage()
{
    INFO << "Recognizing the image";
    QProcess::execute(OCR_IMG2TXT);
//    QProcess::execute("cat /opt/freedict/out.txt");
    QFile file(OCR_RES_PATH);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        INFO << "Failed to read the out.txt: " << OCR_RES_PATH;
        return false;
    } else {
        QTextStream in(&file);
        QString ocr_result;
        QString line = in.readLine();
        while (!line.isNull()) {
            INFO << "readline";
            ocr_result.append(line);
            line = in.readLine();
        }
        INFO << "The ocr_result is:" << ocr_result;
        src_word = ocr_result.trimmed();
        query();
        //line_edit of float_browser get focus
        float_browser->input->setText(src_word);
        float_browser->input->selectAll();
        float_browser->input->setFocus();
        return true;
    }
}

void MainWindow::trayIconActived(QSystemTrayIcon::ActivationReason reason)
{
    // 响应托盘的事件
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        INFO << "System tray trigger";
        this->show();
        break;
    case QSystemTrayIcon::Context:
        INFO << "Context";
        break;
    default:
        break;
    }
}

void MainWindow::query()
{
//    查询
    youdao_api->translate(src_word,
                          src_language->currentText(),
                          des_language->currentText());
}

void MainWindow::onReplyGot()
{
    Result *result = youdao_api->result;
    if (result->error_code != 0)
    {
        this->des_word = "查询失败，请检查网络, error code:" + result->error_code;
        show_result(this->des_word);
        INFO << "Query failed";
    }
    else {
        this->des_word =
                "音标：US[ " + result->us_phonetic + " ] UK[ "
                + result->uk_phonetic +" ]\n"
                + "翻译：" + result->translation
                + "解释：\n" + result->explain;
        INFO << "query finished";
        show_result(this->des_word);
//        sqlite.save(src_word, des_word, "history");
    }
}

void MainWindow::show_result(QString res)
{
//    显示查询结果
    switch (who_query) {
    case Requestor::MainWindowE:
        browser->setText(res); break;
    default:
        float_browser->browser->setText(res);
    }
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == button_time && !float_button->isMouseOn())
    {
        float_button->setVisible(false);
        button_time = 0;
    }
}

void MainWindow::onButtonPressed()
{
    this->isButtonPressed = true;
    picker->buttonPressed();
//    隐藏悬浮按钮
    if (float_browser->isVisible() && !float_browser->isMouseOn()) {
        float_browser->setVisible(false);
        DEBUG << "Hide the float browser ***************";
    }

    if (float_button->isVisible() && !float_button->isMouseOn()) {
        float_button->setVisible(false);
        DEBUG << "Hide the float button *************";
    }
}

void MainWindow::onButtonReleased(int x, int y)
{
    this->isButtonPressed = false;
    picker->buttonReleased();
//    // 对浏览器的特殊优化，浏览器网页内选中文本，鼠标还没有释放就会发送选中文本变化的信号
//    // 检测选中的文本是否改变
//    if (this->is_selection_changed)
//    {
//        this->queryByMode();
//        this->is_selection_changed = false;
//    }
}

void MainWindow::onFloatButtonClicked() {
    who_query = Requestor::FloatButtonE;
    float_browser->browser->setText(tr("正在查询"));
    query();
    float_browser->move(QCursor::pos().x() - 10, QCursor::pos().y() - 10);

    INFO << "Show the float browser";
//    float_browser->setVisible(true);
    float_browser->show();

    //line_edit of float_browser get focus, then wait for the query reply
    float_browser->input->setText(src_word);
    float_browser->input->selectAll();
    float_browser->input->setFocus();
}

void MainWindow::showAbout()
{
    about_window = new About;
    about_window->show();
}

void MainWindow::showSetting() {
    settings_window->show_options();
}

void MainWindow::onWordsPicked(QString text)
{
    this->src_word = text;
    DEBUG << "Text got:" << text;
    this->queryByMode();
}
