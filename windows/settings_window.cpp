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
#include "settings_window.h"
#include <QDebug>


SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("设置"));
    layout_root = new QFormLayout(this);
    config = new QSettings("/opt/words-picker/conf", QSettings::IniFormat);

    ocr = new QPushButton(tr("关"));
    ocr->setToolTip(tr("识别剪切板的图像中的文字"));
    selected = new QPushButton(tr("关"));
    selected->setToolTip(tr("鼠标选中文本时弹出翻译按钮"));
    auto_translate = new QPushButton(tr("关"));
    auto_translate->setToolTip(tr("选中文本之后自动翻译"));

    layout_root->addRow(tr("截图翻译"), ocr);
    layout_root->addRow(tr("选中翻译"), selected);
    layout_root->addRow(tr("自动翻译"), auto_translate);
    this->signalSlot();
    load_settings();
}

void SettingsWindow::signalSlot()
{
    connect(ocr, &QPushButton::clicked,
            this, [=]{
        if (ocr->text() == "开"){
            ocr->setText("关");
            config->setValue("switch/ocr", "false");
        } else {
            ocr->setText("开");
            config->setValue("switch/ocr", "true");
        }
        load_settings();
    });

    connect(selected, &QPushButton::clicked,
            this, [=]{
        if (selected->text() == "开"){
            selected->setText("关");
            config->setValue("switch/selected", "false");
        } else {
            selected->setText("开");
            config->setValue("switch/selected", "true");
        }
        load_settings();
    });

    connect(auto_translate, &QPushButton::clicked,
            this, [=]{
        if (auto_translate->text() == "开"){
            auto_translate->setText("关");
            config->setValue("switch/auto_translate", "false");
        } else {
            auto_translate->setText("开");
            config->setValue("switch/auto_translate", "true");
        }
        load_settings();
    });
}

QMap<QString, QString> * SettingsWindow::load_settings()
{
    setting_map = new QMap<QString, QString>;
    QString is_ocr = config->value("switch/ocr").toString();
    QString is_selected = config->value("switch/selected").toString();
    QString is_auto_translate = config->value("switch/auto_translate").toString();
    setting_map->insert("is_ocr", is_ocr);
    setting_map->insert("is_selected", is_selected);
    setting_map->insert("is_auto_translate", is_auto_translate);

    return setting_map;
}

void SettingsWindow::show_options()
{
    //QMap<QString, QString> res = load_settings();
    /*
    QMap<QString, QString>::const_iterator i = ;
    QString is_ocr = i.value();
    QMap<QString, QString>::const_iterator i = res.find("is_selected");
    QString is_selected = i.value();
    while (i != res.end() && i.key() == "is_ocr") {
        QString is_ocr = i.value();
        qDebug() << is_ocr;
        ++i;
    }
    */

    if (setting_map->find("is_ocr").value() == "true"){
        ocr->setText("开");
    }
    if (setting_map->find("is_selected").value() == "true"){
        selected->setText("开");
    }
    if (setting_map->find("is_auto_translate").value() == "true"){
        auto_translate->setText("开");
    }

    show();
}
