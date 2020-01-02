#ifndef WORD_TABLE_H
#define WORD_TABLE_H
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>
#include "../SQL/sqlite.h"
#include <QComboBox>
#include <QMenu>
#include <QAction>
#include <QPoint>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

class Word_table : public QWidget
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
    QMenu *menu;
    QAction *action_delete;
    QAction *action_test;
    void build_menu();
    QVBoxLayout *layout_root;
    QHBoxLayout *layout_buttonArea;
private slots:
    void show_menu(const QPoint pos);
};

#endif // WORD_TABLE_H
