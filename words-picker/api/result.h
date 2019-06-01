#ifndef RESULT_H
#define RESULT_H
# include <QByteArray>
#include <QString>
#include <QObject>

// todo 搞清楚为什么不继承自QObject就会出现构造函数未定义的情况
class Result: public QObject
{
    Q_OBJECT
public:
    Result(QByteArray res);
    ~Result();
    QString translation;
    QString us_phonetic;
    QString uk_phonetic;
    QString explain;
    int error_code;
    QString error_msg;
};

#endif // RESULT_H
