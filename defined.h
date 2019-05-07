/*用于存放一些宏定义*/
#ifndef DEFINED_H
#define DEFINED_H
#include <QDebug>

#define DEBUG qDebug() << "DEBUG" << __FILE__ << __LINE__
#define INFO qDebug() << "INFO" << __FILE__ << __LINE__
#define WARNING qDebug() << "WARNING" << __FILE__ << __LINE__
#define ERROR qDebug() << "ERROR" << __FILE__ << __LINE__
#endif // DEFINED_H
