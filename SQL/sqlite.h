#ifndef SQLITE_H
#define SQLITE_H
//#include <QSqlDatabase>
#include <QStandardItemModel>
#include <QMessageBox>
// todo cmake included
#include <QtSql/QSqlDatabase>

class SQLite
{
public:
    SQLite();
    bool save(QString word, QString result, QString sort);
    QSqlDatabase db;
    bool create();
    bool derive(QString field);
    bool exec(QString sql);
    bool word_table(QStandardItemModel *modle, QString sort);
};

#endif // SQLITE_H
