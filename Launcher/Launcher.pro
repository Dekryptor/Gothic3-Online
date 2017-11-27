#-------------------------------------------------
#
# Project created by QtCreator 2015-07-05T11:19:13
#
#-------------------------------------------------

QT       += core gui
QT +=  webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Launcher
TEMPLATE = app
RC_FILE = Launcher.rc


SOURCES += main.cpp\
        mainwindow.cpp \
    MemLib.cpp \
    simplecrypt.cpp

HEADERS  += mainwindow.h \
    MemLib.h \
    simplecrypt.h

FORMS    += mainwindow.ui

DISTFILES += \
    background.jpg \
    Launcher.rc

RESOURCES += \
    resources.qrc
