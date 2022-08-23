/*用于存放一些宏定义*/
#ifndef DEFINED_H
#define DEFINED_H
#include <QDebug>

#define DEBUG qDebug() << "DEBUG" << __FILE__ << __LINE__
#define INFO qDebug() << "INFO" << __FILE__ << __LINE__
#define WARNING qDebug() << "WARNING" << __FILE__ << __LINE__
#define ERROR qDebug() << "ERROR" << __FILE__ << __LINE__

#define APP_NAME QString("words-picker")

#define SYSTEM_TMP_PATH QString("/tmp")
#define INFO_FILE_PATH QString(SYSTEM_TMP_PATH + "/" + APP_NAME + "/info")
// out会自动加上txt后缀
#define OCR_IMG_PATH QString(SYSTEM_TMP_PATH  + "/" + APP_NAME + "/ocr.png")
#define OCR_RES_PATH QString(SYSTEM_TMP_PATH + "/" + APP_NAME + "/out.txt")
#define OCR_IMG2TXT QString("tesseract " + OCR_IMG_PATH + " " + SYSTEM_TMP_PATH + "/" + APP_NAME + "/out")

//#define IS_DEV true
#define IS_DEV true
// #define BASE_URL QString("http://localhost:8000")
#define BASE_URL QString("http://opensource.test.passer.zyheal.com:8000")

#endif // DEFINED_H
