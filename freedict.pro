#-------------------------------------------------
#
# Project created by QtCreator 2017-08-31T18:10:50
#
#-------------------------------------------------

QT       += core gui network widgets x11extras dbus sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = freedict
INCLUDEPATH +=. \
#              /usr/include/
TEMPLATE = app
CONFIG += link_pkgconfig c++11
PKGCONFIG += xcb xcb-util
LIBS += -lX11 -lXext -lXtst

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    api/youdaoapi.cpp \
    windows/float_button.cpp \
    windows/float_browser.cpp \
    event/eventmonitor.cpp \
    SQL/sqlite.cpp \
    windows/about.cpp \
    windows/word_table.cpp \
    systemtrayicon.cpp \
    windows/hyaline_window.cpp \
    windows/settings_window.cpp

HEADERS += \
        mainwindow.h \
    api/youdaoapi.h \
    windows/float_button.h \
    windows/float_browser.h \
    event/eventmonitor.h \
    SQL/sqlite.h \
    windows/about.h \
    windows/word_table.h \
    systemtrayicon.h \
    windows/hyaline_window.h \
    windows/settings_window.h

RESOURCES += \
    src.qrc

QMAKE_CXXFLAGS += -g
