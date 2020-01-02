#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QClipboard>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void dll_test();
    QPushButton *hook_on = NULL;
    QPushButton *hook_off = NULL;
    void set_timer();
    QTimer *timer = NULL;
    QClipboard *board;
};

#endif // MAINWINDOW_H
