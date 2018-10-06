#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QApplication"
#include <QDebug>
#include <windows.h>
#include <winbase.h>
#include <winuser.h>


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    board = QApplication::clipboard();
    //Load the dll
    //String *lpFileName = "dlltest.dll";
    //HMODULE hMoudle = LoadLibrary(lpFileName);
    HMODULE hMoudle = LoadLibraryA("C:\\Users\\ziqiang_xu\\Documents\\build-dlltest-Desktop_Qt_5_9_6_MinGW_32bit-Debug\\debug\\dlltest.dll");

    /*如果返回码是126则表示未找到模块.
     * 其它值查阅:
     * https://msdn.microsoft.com/en-us/library/ms681382(v=vs.85).aspx
*/
    qDebug() << "The lastError is:" << GetLastError();

    if(hMoudle == NULL){
        //MessageBoxA(NULL, "dll not exist!", "failed to load the dll", MB_OK);
        qDebug() << "failed to load the dll!";
    }
    else {
        //MessageBoxA(NULL, "success!", "success to load the dll", MB_OK);
        //FUNT Funt1 = (FUNT)GetProcAddress(Hint, "test1");
        qDebug() << "success to load the dll!";
    }
    typedef int (*FUNT)();
    FUNT test1 = (FUNT)GetProcAddress(hMoudle, "test1");
    FUNT SetHookOn = (FUNT)GetProcAddress(hMoudle, "SetHookOn");
    FUNT SetHookOff = (FUNT)GetProcAddress(hMoudle, "SetHookOff");
    qDebug() << "The lastError is:" << GetLastError();  //127表示无法找到指定的dll函数

    hook_on = new QPushButton(this);
    hook_on->setText("hook_on");
    hook_on->move(30, 80);

    hook_off = new QPushButton(this);
    hook_off->setText("hook_off");
    hook_off->move(180, 80);

    /*
    qDebug() << "CALL: begin";
    SetHookOn();
    test1();
    qDebug() << "CALL: end";
    */
    set_timer();

    QObject::connect(hook_on, &QPushButton::clicked,
                     this, [=]{
        SetHookOn();
    });
    QObject::connect(hook_off, &QPushButton::clicked,
                     this, [=]{
        SetHookOff();
    });
    QObject::connect(board, &QClipboard::changed,
                     this, [=]{
        qDebug() << "This is the changed signal";

    });
    QObject::connect(board, &QClipboard::dataChanged,
                     this, [=]{
        qDebug() << "This is the dataChanged signal";
    });
    QObject::connect(board, &QClipboard::selectionChanged,
                     this, [=]{
        qDebug() << "This is the selectionChanged signal";
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dll_test()
{
    qDebug() << "dll_test() executed!";
}

void MainWindow::set_timer()
{
    timer = new QTimer(this);
    timer->start(1000);
    QObject::connect(timer, &QTimer::timeout,
            this, [=]{
       qDebug() << "timer timeout:" << board->text(QClipboard::Selection) << board->text(QClipboard::Clipboard);
    });
}
