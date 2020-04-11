#include "picker.h"
#include <QApplication>
#include "defined.h"

Picker::Picker()
{
    clipboard = QApplication::clipboard();
    connect(clipboard, &QClipboard::selectionChanged,
            this, [=] {
        // do not emit the signal right now, for browser
        if (!isPressed) {
            text = clipboard->text(QClipboard::Selection);
            emit wordsPicked(text);
        }
    });
}

void Picker::buttonPressed()
{
    this->text = "";
    this->isPressed = true;
}

void Picker::buttonReleased()
{
    this->isPressed = false;
    // to get the selected text
    INFO << "Text from picker" << text;
    if (text != "") emit wordsPicked(text);
}

QString Picker::getSelectedText()
{
    return clipboard->text(QClipboard::Selection);
//    return "Picker";
}
