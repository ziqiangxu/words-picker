#ifndef PICKER_H
#define PICKER_H
#include <QString>
#include <QObject>
#include <QClipboard>
#include <QProcess>

class Picker:public QObject
{
    Q_OBJECT  // Signals need this
public:
    Picker();
    // 鼠标左键按下进行的处理，暂无
    void buttonPressed();

    // 鼠标左键释放进行的处理：如果选中文本发生变化，则发送wordsPicked信号
    void buttonReleased();

    // 获取Linux系统选中的文本
    QString getSelectedText();

    // 发送wordsPicked信号之前的选中的文本
    QString pre_text;

    // 当前选中的文本
    QString current_text;

private:
    QProcess* process;

signals:
    void wordsPicked(QString);
};

#endif // PICKER_H
