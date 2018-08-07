#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QFormLayout>

class SettingsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsWindow(QWidget *parent = nullptr);
private:
    QFormLayout *layout_root;
    void load_settings();

signals:

public slots:
};

#endif // SETTINGSWINDOW_H
