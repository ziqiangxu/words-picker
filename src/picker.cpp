#include "picker.h"
#include <QApplication>
#include <QByteArray>
#include "defined.h"

Picker::Picker()
{
    process = new QProcess();

    // 初始化Picker的时候保证pre_text和current_text一致，防止第一次按钮释放的时候：
    // 出现pre_text为null，而current_text有值，触发wordsPicked信号
    pre_text = getSelectedText();
    current_text = pre_text;
}

void Picker::buttonPressed()
{
}


// 比对之前的选中文本和当前的文本，如果发生改变，则表示在进行文本选中操作，
// 发送wordsPicked信号。
void Picker::buttonReleased()
{
    current_text = getSelectedText();
    DEBUG << current_text << pre_text;
    if (current_text != pre_text) {
        emit wordsPicked(current_text);
        pre_text = current_text;
    }
}


// 使用xsel命令获取最近一次选中的文本
QString Picker::getSelectedText()
{    process->start("xsel");
    process->waitForFinished();
    QString selected_text = *new QString(process->readAllStandardOutput());
    return selected_text;
}
