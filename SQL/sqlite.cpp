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
    db.setDatabaseName("dict.sqlite");
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
        return false;
    }

    int times = 1;
    QSqlQuery query;
    query.prepare("insert into history (word, result, sort, times)"
                  "values (:word, :result, :sort, :times)");
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
    if (query.exec("create table history(word varchar primary key,result varchar NOT NULL,sort varchar NOT NULL,times int)"))
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
    //QString sort,times;
    db.open();
    QSqlQuery query;
    QString sql = "SELECT * FROM history WHERE sort LIKE '";
    sql += sort + "'";
    if (query.exec(sql))
    {
        QString home_path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
        QFile file(home_path + "/Desktop/" + sort + ".txt");
        if (!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox::critical(NULL, QObject::tr("错误"), QObject::tr("无法创建文件"));
        }
        else {
            QTextStream out(&file);
            while (query.next())
            {
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
    db.close();
    return false;
}

bool SQLite::exec(QString sql)
{
    db.open();
    QSqlQuery query;
    if (query.exec(sql)) return true;
    else return false;
}
