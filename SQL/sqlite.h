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
    bool derive_new();
};

#endif // SQLITE_H
