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
#include "sqlite.h"
#include <QRegularExpression>
#include <QSqlQuery>
#include <QDebug>
#include <QDesktopServices>
#include <QFile>
#include <QMessageBox>

SQLite::SQLite()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/opt/freedict/dict.sqlite");
    create();
}

bool SQLite::save(QString word, QString result, QString sort)
{    
    db.open();
    QString partten = "^ ?[a-z]+ ?$";
    QRegularExpression re(partten, QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = re.match(word);
    if (!match.hasMatch())
    {
        qDebug() << "Queried the word but not a single word";
        db.close();
        return false;
    }

    int times = 1;
    QSqlQuery query;
    query.prepare("INSERT INTO history (word, result, sort, times)"
                  "VALUES (:word, :result, :sort, :times)");
    query.bindValue(":word", word);
    query.bindValue(":result", result);
    query.bindValue(":sort", sort);
    query.bindValue(":times",times);
    if(query.exec())
    {
        qDebug("result saved in sqlite");
        db.close();
        return true;
    }
    db.close();
    qDebug("result saving failed,perhaps the word exist already.");
    return false;
}

bool SQLite::create()
{
    db.open();
    QSqlQuery query;
    if (query.exec("CREATE TABLE history(word VARCHAR PRIMARY KEY,result VARCHAR NOT NULL,sort VARCHAR NOT NULL,times INT)"))
    {
        db.close();
        return true;
    }
    db.close();
    return false;
}

bool SQLite::derive(QString sort)
{
    QString word,result;
    db.open();
    QSqlQuery query;
    QString sql = "SELECT * FROM history WHERE sort LIKE '";
    sql += sort + "'";
    if (query.exec(sql))
    {
        QString home_path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
        if (sort == "%") sort = "history";
        QFile file(home_path + "/Desktop/" + sort + ".txt");
        if (!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox::critical(NULL, QObject::tr("错误"), QObject::tr("无法创建文件"));
        }
        else {
            QTextStream out(&file);
            while (query.next()){
                word = query.value(0).toString();
                result = query.value(1).toString();
                out << word << endl << result << "\n----------------------------------------\n" << endl;
                /*
                sort = query.value(2).toString();
                times = query.value(3).toString();
                qDebug() << " word:" <<word;
                qDebug() << "\n result:" <<result;
                qDebug() << "\n sort:" << sort;
                qDebug() << "\n times:" << times;
                */
            }
            file.close();
            db.close();
            return true;
        }
    }
    else {
        QMessageBox::warning(NULL, QObject::tr("警告!"), QObject::tr("请检查您输入的类别"));
        db.close();
    }
    return false;
}

bool SQLite::exec(QString sql)
{
    db.open();
    QSqlQuery query;
    if (query.exec(sql)){
        db.close();
        return true;
    }
    else{
        db.close();
        return false;
    }
}

bool SQLite::word_table(QStandardItemModel *modle, QString sort)
{
    QString sql,word,result;
    sql = "SELECT * FROM history WHERE sort LIKE '";
    sql.append(sort).append("'");
    db.open();
    QSqlQuery query;
    if (query.exec(sql))
    {
        int i = 0;
        while (query.next()) {
            word = query.value(0).toString();
            result = query.value(1).toString();
            modle->setItem(i, 0, new QStandardItem(word));
            modle->setItem(i, 1, new QStandardItem(result));
            i++;
        }
        db.close();
        return true;
    }
    else {
        db.close();
        return false;
    }
}
