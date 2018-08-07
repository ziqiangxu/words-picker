#include "settings_window.h"
#include <QPushButton>

SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent)
{
    layout_root = new QFormLayout(this);
    layout_root->addRow(tr("截图翻译"), new QPushButton("ON"));
}

void SettingsWindow::load_settings()
{

}
