#-------------------------------------------------
#
# Project created by QtCreator 2017-12-12T23:04:29
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VERSION = 1.0.0
QMAKE_TARGET_COMPANY = FdG Studio
QMAKE_TARGET_PRODUCT = I am Developer
QMAKE_TARGET_DESCRIPTION = Developer tool
QMAKE_TARGET_COPYRIGHT = Fidan Gallyamov

TARGET = connect
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    form.cpp \
    picture.cpp

HEADERS  += mainwindow.h \
    form.h \
    picture.h

FORMS    += mainwindow.ui \
    form.ui \
    picture.ui

RC_ICONS = icon.ico
RESOURCES += \
    resources.qrc
