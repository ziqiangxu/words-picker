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
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QApplication>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    clipboard = QApplication::clipboard();
    sqlite = SQLite();

    build_GUI();
    youdao_api = new YoudaoAPI;
    signals_slots();
    //*Test area
    //setStyleSheet("background-color:blue");
    //*/
}

MainWindow::~MainWindow()
{
    delete input;
    delete exchange_language;
    delete about;
    delete derive;
    delete src_language;
    delete des_language;
    delete browser;
}

void MainWindow::build_GUI()
{
    move(100,100);
    setFixedSize(400,270);

    input = new QLineEdit(this);
    input->setGeometry(20,10,230,30);
    input->setText(clipboard->text());
    input->selectAll();

    browser = new QTextBrowser(this);
    browser->setGeometry(20,50,230,200);

    exchange_language = new QPushButton(this);
    exchange_language->move(280,50);
    exchange_language->setText(tr("交换语言"));
    exchange_language->adjustSize();
    QSize button_size = exchange_language->size();

    src_language = new QComboBox(this);
    src_language->move(280,10);
    src_language->setFixedSize(button_size);
    des_language = new QComboBox(this);
    des_language->move(280,90);
    des_language->setFixedSize(button_size);
    init_language();

    derive = new QPushButton(this);
    derive->setText(tr("导出生词"));
    derive->move(280,130);
    derive->setFixedSize(button_size);

    about = new QPushButton(this);
    about->setText(tr("关于"));
    about->move(280,210);
    about->setFixedSize(button_size);

    float_button = new Float_Button;
    float_browser = new Float_Browser;


    about_window = new About;


    //*Test area
    //setWindowFlags(Qt::WindowStaysOnTopHint);
    //*/
}

void MainWindow::init_language()
{
    QStringList language;
    language << "EN" << "zh_CHS" << "ja" << "ko" << "fr" << "ru"
         << "pt" << "es";
    src_language->addItems(language);
    des_language->addItems(language);
    src_language->setCurrentIndex(0);
    des_language->setCurrentIndex(1);
}

void MainWindow::signals_slots()
{
    connect(youdao_api, &YoudaoAPI::finish,
            this,&MainWindow::get_result);

//------Response the "mainwindow"
    //Query when "Enter" pressed in "input"
    connect(input, &QLineEdit::returnPressed,
            this, [=]{
        src_word = input->text();
        who_query = Requestor::Mainwindow;
        query();
        browser->setText(tr("查询中"));
        input->selectAll();
        if (sender() == input) qDebug() << "test complite!";
        qDebug() << "The sender is:" << sender();
    });

    //"input" get focus when language changed
    connect(exchange_language,&QPushButton::clicked,
            this, [=]{
        int int_temp = src_language->currentIndex();
        src_language->setCurrentIndex(des_language->currentIndex());
        des_language->setCurrentIndex(int_temp);
        input->setFocus();
    });
    /*Note: Signal activated is overloaded in this class. To connect to this one
     *  using the function pointer syntax, you must specify the signal type in a
     *  static cast*/
    connect(src_language, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated),
            this,[=]{input->setFocus();});
    connect(des_language, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated),
            this, [=]{input->setFocus();});
//------Response the "float_button"
    //Show "float_button" when the selected text changed,it's not a button but a window in fact
    connect(clipboard, &QClipboard::selectionChanged,
            float_button, [=]{
        float_button->setVisible(true);
        float_button->move(QCursor::pos().x() + 10, QCursor::pos().y() + 10);
        button_time = startTimer(5000);
    });

    //Show "float_browser" after clicked the "float_button"
    connect(float_button, &Float_Button::clicked,
            float_browser, [=]{
        src_word = qApp->clipboard()->text(QClipboard::Selection);
        who_query = Requestor::Float_button;
        float_browser->browser->setText(tr("正在查询"));
        query();
        float_browser->move(QCursor::pos());
        float_browser->setVisible(true);
        float_button->setVisible(false);
        //line_edit of float_browser get focus
        float_browser->input->setText(src_word);
        float_browser->input->selectAll();
        float_browser->input->setFocus();
    });
//------Response the "float_browser"
    connect(float_browser->input, &QLineEdit::returnPressed,
            this, [=]{
        src_word = float_browser->input->text();
        who_query = Requestor::Float_browser;
        query();
        float_browser->browser->setText(tr("正在查询"));
        float_browser->input->selectAll();
    });

    connect(float_browser->query, &QPushButton::clicked,
            this, [=]{
        src_word = float_browser->input->text();
        who_query = Requestor::Float_browser;
        query();
        float_browser->browser->setText(tr("正在查询"));
        float_browser->input->selectAll();
    });

    connect(float_browser->add_new, &QPushButton::clicked,
            this, [=]{
        QString sql("UPDATE history SET sort='new' WHERE word='");
        sql += src_word + "'";
        sqlite.exec(sql);
    });

    connect(float_browser->google_translate, &QPushButton::clicked,
            this, [=]{
        qDebug() << src_language->currentText() << des_language->currentText();
        src_word = float_browser->input->text();
        float_browser->google_web_translate(src_word,
                                            src_language->currentText(),
                                            des_language->currentText());
    });

//------Response the "about"
    connect(about, &QPushButton::clicked,
            this, [=]{
        show_about();
        input->setFocus();
    });

//------Response the "derive"
    connect(derive, &QPushButton::clicked,
            this, [=]{
        derive_words();
        input->setFocus();
    });
}

void MainWindow::query()
{
    youdao_api->translate(src_word,
                          src_language->currentText(),
                          des_language->currentText());
}

void MainWindow::get_result(QByteArray re)
{
    qDebug() << "the reply text:" <<QString(re);

    QJsonDocument json_doc = QJsonDocument::fromJson(re);
    QJsonObject json_obj = json_doc.object();
    QStringList L1 = json_obj.keys();
    qDebug() << "the reply keys:" <<L1;

    //Get the translatin
    QJsonArray translation_array = json_obj.take("translation").toArray();
    int counter = translation_array.count();
    QString translation;
    for (int i = 0; i < counter; i++)
    {
        translation.append(translation_array.at(i).toString() + "\n");
    }

    //Get the web：explain from the web
    QJsonArray web_array = json_obj.take("web").toArray();
    QString web;
    counter = web_array.count();
    for (int i = 0; i < counter; i++)
    {
        web.append(web_array.at(i).toString() + "\n");
    }

    //Get the basic：contain almost information we need
    QJsonObject basic_obj = json_obj.take("basic").toObject();

    QString us_phonetic = basic_obj.take("us-phonetic").toString();
    QString uk_phonetic = basic_obj.take("uk-phonetic").toString();
    QString phonetic = basic_obj.take("phonetic").toString();

        //Get the explains in basic_obj
    QJsonArray explains_array = basic_obj.take("explains").toArray();
    QString explains;
    counter = explains_array.count();
    for (int i = 0; i < counter; i++){
        explains.append(explains_array.at(i).toString() + "\n");
    }
    qDebug() << "explains" << ":" << explains;

    //Get the way of translation：from English to Chinese-simple as the default way
    QString language = json_obj.take("l").toString();
    qDebug() << "way of translation:" << language;

    //Get the erroCode：0 means everything on it's way.You can get more from
    //http://ai.youdao.com/docs/api.s
    int erroCode = json_obj.take("erroCode").toInt();

    //Save the result in the database
    if (translation_array.isEmpty() || erroCode != 0)
    {
        des_word = "查询失败，请检查网络";
        show_result();
        qDebug() << "Query failed";
    }
    else {
        des_word =
                "音标：US[ " + us_phonetic + " ] UK[ " + uk_phonetic +" ]\n"
                + "翻译：" +translation
                + "解释：\n" +explains;
        qDebug() << "query finished";
        show_result();
        sqlite.save(src_word, des_word, "history");
    }
}

void MainWindow::show_result()
{
    switch (who_query) {
    case Requestor::Float_browser:
        qDebug() << "QLineEdit object--input of mainwindow request";
        float_browser->browser->setText(des_word);
        break;
    case Requestor::Float_button:
        qDebug() << "QLineEdit object--input of mainwindow request";
        float_browser->browser->setText(des_word);
        break;
    default:
        qDebug() << "QLineEdit object--input of mainwindow request";
        browser->setText(des_word);
        break;
    }
}

void MainWindow::hide_float()
{
    if (float_browser->isVisible() && !float_browser->isMouseOn())
        float_browser->setVisible(false);

    if (float_button->isVisible() && !float_browser->isMouseOn())
        float_button->setVisible(false);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == button_time && !float_button->isMouseOn())
    {
        float_button->setVisible(false);
        button_time = 0;
    }
}

void MainWindow::show_about()
{
    about_window = new About;
    about_window->show();
}

void MainWindow::derive_words()
{
    SQLite sqlite;
    if (sqlite.derive("new"))
    {
        QMessageBox::about(this, tr("提示"), tr("导出生词成功！文件已保存到桌面“new.txt”"));
    }
    else {
        QMessageBox::critical(this, tr("警告"), tr("非常抱歉，导出生词出错！"));
    }
}
