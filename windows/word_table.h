#ifndef WORD_TABLE_H
#define WORD_TABLE_H
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>
#include "SQL/sqlite.h"
#include <QComboBox>

class Word_table
{
public:
    Word_table();
    ~Word_table();
    SQLite *sqlite;
    QTableView *table;
    QStandardItemModel *modle;
    QPushButton *remove;
    QPushButton *derive;
    QComboBox *sort;
    void get_word();
    void derive_word();
    void signals_slots();
    void remove_selection();
private:
    void buildGUI();
};

#endif // WORD_TABLE_H
