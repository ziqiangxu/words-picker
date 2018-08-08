#include "settings_window.h"
#include <QDebug>


SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("设置"));
    layout_root = new QFormLayout(this);
    config = new QSettings("/opt/freedict/freedict.conf", QSettings::IniFormat);
    load_settings();
}

QMap<QString, QString> * SettingsWindow::load_settings()
{
    setting_map = new QMap<QString, QString>;
    QString is_ocr = config->value("switch/ocr").toString();
    QString is_selected = config->value("switch/selected").toString();
    setting_map->insert("is_ocr", is_ocr);
    setting_map->insert("is_selected", is_selected);
    return setting_map;
}

void SettingsWindow::show_options()
{
    //QMap<QString, QString> res = load_settings();
    /*
    QMap<QString, QString>::const_iterator i = ;
    QString is_ocr = i.value();
    QMap<QString, QString>::const_iterator i = res.find("is_selected");
    QString is_selected = i.value();
    while (i != res.end() && i.key() == "is_ocr") {
        QString is_ocr = i.value();
        qDebug() << is_ocr;
        ++i;
    }
    */
    ocr = new QPushButton("关");
    selected = new QPushButton("关");
    layout_root->addRow(tr("截图翻译"), ocr);
    layout_root->addRow(tr("选中翻译"), selected);

    if (setting_map->find("is_ocr").value() == "true"){
        ocr->setText("开");
    }
    if (setting_map->find("is_selected").value() == "true"){
        selected->setText("开");
    }

    connect(ocr, &QPushButton::clicked,
            this, [=]{
        if (ocr->text() == "开"){
            ocr->setText("关");
            config->setValue("switch/ocr", "false");
        } else {
            ocr->setText("开");
            config->setValue("switch/ocr", "true");
        }
        load_settings();
    });

    connect(selected, &QPushButton::clicked,
            this, [=]{
        if (selected->text() == "开"){
            selected->setText("关");
            config->setValue("switch/selected", "false");
        } else {
            selected->setText("开");
            config->setValue("switch/selected", "true");
        }
        load_settings();
    });

    show();
}
