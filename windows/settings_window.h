#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QFormLayout>
#include <QSettings>
#include <QPushButton>
#include <QMap>

class SettingsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    QMap <QString, QString> *load_settings();
    void show_options();
    QMap<QString, QString> * setting_map;
private:
    QFormLayout *layout_root;
    QSettings *config;
    QPushButton *ocr, *selected;


signals:

public slots:
};

#endif // SETTINGSWINDOW_H
