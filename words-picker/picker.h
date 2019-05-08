#ifndef PICKER_H
#define PICKER_H
#include <QString>
#include <QObject>
#include <QClipboard>

class Picker:public QObject
{
    Q_OBJECT  // Signals need this
public:
    Picker();
    void buttonPressed();
    void buttonReleased();
    QString getSelectedText();
    QString text;

private:
    QClipboard *clipboard;
    bool isPressed;

signals:
    void wordsPicked(QString);
};

#endif // PICKER_H
