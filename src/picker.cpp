#include "picker.h"
#include <QApplication>
#include <QByteArray>
#include "defined.h"

Picker::Picker()
{
    clipboard = QApplication::clipboard();
    connect(clipboard, &QClipboard::selectionChanged,
            this, [=] {
        // do not emit the signal right now, for browser
        // 浏览器不停地触发selection changed事件，导致大开销
        if (!isPressed) {
            current_text = clipboard->text(QClipboard::Selection);
            emit wordsPicked(current_text);
        }
    });

    // text copyed
//    connect(clipboard, &QClipboard::changed,
//            this, [=] {
//        emit wordsPicked(clipboard->text());
//    });
}

void Picker::buttonPressed()
{
    DEBUG << "button pressed";
}


// 比对之前的选中文本和当前的文本，如果发生改变，则表示在进行文本选中操作，
// 发送wordsPicked信号。
void Picker::buttonReleased()
{
    return;

    // todo solve the xsel bug
    current_text = getSelectedText();
    DEBUG << "button released:" << current_text << pre_text;
    if (current_text != pre_text) {
        emit wordsPicked(current_text);
        pre_text = current_text;
    }
}


// 使用xsel命令获取最近一次选中的文本
QString Picker::getSelectedText()
{
    process = new QProcess();
//     在这里面启动它居然要开始死机了
    process->start("/usr/bin/xsel");
    process->waitForFinished();
    QString selected_text = *new QString(process->readAllStandardOutput());
    return selected_text;
}
