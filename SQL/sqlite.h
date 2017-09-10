#ifndef SQLITE_H
#define SQLITE_H
#include <QSqlDatabase>

class SQLite
{
public:
    SQLite();
    bool save(QString word, QString result, QString sort);
    QSqlDatabase db;
    bool create();
    bool derive(QString field);
    bool exec(QString sql);
};

#endif // SQLITE_H
