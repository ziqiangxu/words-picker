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
#include "word_table.h"
#include <QTableView>
#include <QStandardItemModel>
#include "../defined.h"
#include <QMessageBox>
#include "../SQL/sqlite.h"

Word_table::Word_table()
{
    buildGUI();
    sqlite = new SQLite();
    get_word();
    signals_slots();
    show();
}

Word_table::~Word_table()
{
}

void Word_table::signals_slots()
{

    QObject::connect(table, &QTableView::clicked,
                     this, [=]{
        menu->exec(QCursor::pos());
    },Qt::QueuedConnection);


    QObject::connect(sort, &QComboBox::currentTextChanged,
                     table, [=]{
        get_word();
    }, Qt::QueuedConnection);

    QObject::connect(derive, &QPushButton::clicked,
                     table, [=]{
        derive_word();
    });
}

void Word_table::buildGUI()
{
    setWindowTitle(tr("单词管理"));
    layout_root = new QVBoxLayout(this);
    layout_buttonArea = new QHBoxLayout();
    layout_root->addLayout(layout_buttonArea);

    table = new QTableView();
    layout_root->addWidget(table);

    modle = new QStandardItemModel(table);
    modle->setColumnCount(2);
    modle->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("单词"));
    modle->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("解释"));

    sort = new QComboBox();
    sort->setMinimumContentsLength(6);
    sort->addItem(QObject::tr("收藏"), "new");
    sort->addItem(QObject::tr("历史"), "%");
    layout_buttonArea->addWidget(sort);

    layout_buttonArea->addStretch();

    derive = new QPushButton();
    derive->setText("导出");
    layout_buttonArea->addWidget(derive);

    table->setContextMenuPolicy(Qt::CustomContextMenu);
    menu = new QMenu();
    build_menu();
}

void Word_table::build_menu()
{
    action_delete = new QAction(table);
    action_test = new QAction(table);
    action_delete->setText(QObject::tr("删除"));
    connect(action_delete, &QAction::triggered,
            table, [=]{
        DEBUG << "You clicked the action_delete!";
        remove_selection();
    });
    action_test->setText(QObject::tr("Test"));
    menu->addAction(action_delete);
    //menu->addAction(action_test);
}

void Word_table::get_word()
{
    delete modle;
    modle = new QStandardItemModel(table);
    modle->setColumnCount(2);
    modle->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("单词"));
    modle->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("解释"));

    sqlite->word_table(modle, sort->currentData().toString());
    table->setModel(modle);
    table->setColumnWidth(1, 550);
    table->setColumnWidth(0, 100);
    table->setFixedSize(700, 370);
}

void Word_table::derive_word()
{
    QString derive_sort = sort->currentData().toString();
    if (sqlite->derive(derive_sort))
    {
        if (derive_sort == "%") derive_sort = "history";
        QMessageBox::about(table, QObject::tr("提示"),
                           QObject::tr("导出记录成功！文件已保存到桌面“%1.txt”").arg(derive_sort));
    }
    else {
        QMessageBox::critical(table, QObject::tr("警告"),
                              QObject::tr("非常抱歉，导出生词出错！"));
    }
}

void Word_table::remove_selection()
{
    QString content = table->currentIndex().data().toString();
    int column = table->currentIndex().column();
    int row = table->currentIndex().row();
    QString sql = "DELETE FROM history WHERE ";
    switch (column) {
    case 0:
        sqlite->exec(sql.append("word='").append(content).append("'"));
        break;
    default:
        sqlite->exec(sql.append("result='").append(content).append("'"));
        break;
    }
    modle->removeRow(row);
}
